#include <iostream>
#include "controlBlock.hpp"
#include "shared_ptr.hpp"

template <typename T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& weakPtr)
    : controlBlock(weakPtr.expired() ? nullptr : new ControlBlock<T>(weakPtr.lock().get())) 
{
    if (controlBlock != nullptr) {
        ++controlBlock -> sharedCount;
    }
}

template <typename T>
SharedPtr<T>::SharedPtr()
    : controlBlock{nullptr} {}

template <typename T>
SharedPtr<T>::SharedPtr(T value)
        : controlBlock{new ControlBlock<T>{new T(value)}} 
{
    ++controlBlock -> sharedCount;
}

template <typename T> 
SharedPtr<T>::SharedPtr(T* ptr)
        : controlBlock{new ControlBlock<T>{ptr}} 
{
    ++controlBlock -> sharedCount;
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& rhs)
    : controlBlock{rhs.controlBlock}
{
    ++controlBlock -> sharedCount;
    std::cout << controlBlock -> sharedCount;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& rhs) {
    if (this != &rhs) {
        reset();
        controlBlock -> m_ptr = rhs.controlBlock -> m_ptr;
        controlBlock -> sharedCount = rhs.controlBlock -> sharedCount;
        ++controlBlock -> sharedCount;
    }
    std::cout << controlBlock -> shared_count;
    return *this;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& rhs)
    : controlBlock{std::move(rhs.controlBlock)} {
        rhs.controlBlock -> m_ptr = nullptr;
        rhs.controlBlock -> sharedCount = 0;
        rhs.controlBlock -> weakCount = 0;
    }

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& rhs) {
    if (this != &rhs) {
        if (controlBlock -> sharedCount == 0) {
            delete controlBlock -> m_ptr;
        }
        controlBlock = std::move(rhs.controlBlock);
        rhs.controlBlock -> m_ptr = nullptr;
        rhs.controlBlock -> sharedCount = 0;
        rhs.controlBlock -> weakCount = 0;
    }
    return *this;
}

template <typename T>
T* SharedPtr<T>::get() const {
        return controlBlock -> m_ptr;
}
template <typename T>
T& SharedPtr<T>::operator*() const {
    return *controlBlock -> m_ptr;
}

template <typename T>
T* SharedPtr<T>::operator->() const {
    return controlBlock -> m_ptr;;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    reset();
}

template <typename T>
void SharedPtr<T>::reset() {
    if (controlBlock != nullptr) {
        --controlBlock -> sharedCount;
        if (controlBlock -> sharedCount == 0) {
            delete controlBlock;
        }
    }
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr& rhs) {
    using std::swap;

    if (controlBlock != nullptr && rhs.controlBlock != nullptr) {
        swap(controlBlock -> m_ptr, rhs.controlBlock -> ptr);
        swap(controlBlock -> sharedCount, rhs.controlBlock -> sharedCount);
        swap(controlBlock -> weakCount, rhs.controlBlock -> weakCount);
    }
}

template <typename T>
std::size_t SharedPtr<T>::use_count() const {
    if (controlBlock != nullptr) {
        return controlBlock -> sharedCount;
    }
    return 0;
}

template <typename T>
bool SharedPtr<T>::unique() const {
    if (controlBlock != nullptr) {
        return controlBlock -> sharedCount == 1;
    }
    return false;
}