#include <iostream>
#include "controlBlock.hpp"

template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr {
public:
    WeakPtr();
    WeakPtr(const SharedPtr<T>& sharedPtr);
    ~WeakPtr();
    WeakPtr(const WeakPtr& other);
    WeakPtr& operator=(const WeakPtr& other);
    SharedPtr<T> lock() const;
    bool expired() const;
    void reset();

private:
    ControlBlock<T>* controlBlock;
};

template <typename T>
WeakPtr<T>::WeakPtr() : controlBlock(nullptr) {}

template <typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& sharedPtr)
    : controlBlock{sharedPtr.controlBlock} 
{
    if (controlBlock != nullptr) {
        ++controlBlock -> weakCount;
    }
}

template <typename T>
WeakPtr<T>::~WeakPtr() {
    reset();
}

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& other)
    : controlBlock{other.controlBlock}
{
    if (controlBlock != nullptr) {
        ++controlBlock -> weakCount;
    }
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& other) {
    if (this != &other) {
        reset();
        controlBlock = other.controlBlock;
        if (controlBlock != nullptr) {
        ++controlBlock -> weakCount;
    }
    }
    return *this;
}

template <typename T>
SharedPtr<T> WeakPtr<T>::lock() const {
    if (expired()) {
        return nullptr;
    }
    return SharedPtr<T>(*this);
}

template <typename T>
bool WeakPtr<T>::expired() const {
    return controlBlock == nullptr || controlBlock -> sharedCount == 0;
}

template <typename T>
void WeakPtr<T>::reset() {
    if (controlBlock != nullptr) {
        delete controlBlock;
    }
}