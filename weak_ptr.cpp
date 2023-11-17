#include <iostream>
#include "controlBlock.hpp"

template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr {
private:
    ControlBlock<T>* controlBlock;

public:
    WeakPtr() : controlBlock(nullptr) {}

    WeakPtr(const SharedPtr<T>& sharedPtr)
        : controlBlock{sharedPtr.controlBlock} 
    {
        if (controlBlock != nullptr) {
            ++controlBlock -> weakCount;
        }
    }

    ~WeakPtr() {
        reset();
    }

    WeakPtr(const WeakPtr& other)
        : controlBlock{other.controlBlock}
    {
        if (controlBlock != nullptr) {
            ++controlBlock -> weakCount;
        }
    }

    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            reset();
            controlBlock = other.controlBlock;
            if (controlBlock != nullptr) {
            ++controlBlock -> weakCount;
        }
        }
        return *this;
    }

    SharedPtr<T> lock() const {
        if (expired()) {
            return nullptr;
        }
        return SharedPtr<T>(*this);
    }

    bool expired() const {
        return controlBlock == nullptr || controlBlock -> sharedCount == 0;
    }

    void reset() {
        if (controlBlock != nullptr) {
            delete controlBlock;
        }
    }
};

template <typename T>
class SharedPtr {
public:
    explicit SharedPtr(T value)
        : controlBlock{new ControlBlock<T>{new T(value)}} {}

    explicit SharedPtr(T* ptr)
        : controlBlock{new ControlBlock<T>{ptr}} {}

    SharedPtr(const SharedPtr& rhs)
        : controlBlock{rhs.controlBlock}
    {
        ++controlBlock -> sharedCount;
    }

    SharedPtr& operator=(const SharedPtr& rhs) {
        if (this != &rhs) {
            if (controlBlock -> sharedCount <= 0) {
                delete controlBlock -> m_ptr;
            }
            controlBlock -> m_ptr = rhs.controlBlock -> m_ptr;
            controlBlock -> sharedCount = rhs.controlBlock -> sharedCount;
            ++controlBlock -> sharedCount;
        }
        return *this;
    }

    T& operator*() const {
        return *controlBlock -> m_ptr;
    }

    T* operator->() const {
        return controlBlock -> m_ptr;;
    }

    ~SharedPtr() {
        --controlBlock -> sharedCount;
        if (controlBlock -> sharedCount == 0) {
            delete controlBlock -> m_ptr;
            delete controlBlock;
        }
    }
private:
    ControlBlock<T>* controlBlock;
};