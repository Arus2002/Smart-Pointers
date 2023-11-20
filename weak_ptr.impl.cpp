#include "weak_ptr.hpp"

template <typename T>
WeakPtr<T>::WeakPtr() : controlBlock(nullptr) {}

template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr&& other) noexcept 
    : controlBlock{other.controlBlock} 
{
    --controlBlock -> sharedCount;
    --controlBlock -> weakCount;
    other.controlBlock -> m_ptr = nullptr;
    other.controlBlock -> sharedCount = 0;
    other.controlBlock -> weakCount = 0;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
        --controlBlock -> sharedCount;
        --controlBlock -> weakCount;
        if (controlBlock -> sharedCount == 0) {
            delete controlBlock -> m_ptr;
        }
        controlBlock = other.controlBlock;
        other.controlBlock -> m_ptr = nullptr;
        other.controlBlock -> sharedCount = 0;
        other.controlBlock -> weakCount = 0;
    }
}
template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& other)
    : controlBlock{other.controlBlock}
{
    if (controlBlock != nullptr) {
        ++controlBlock -> weakCount;
        ++other.controlBlock -> weakCount;
    }
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& other) {
    if (this != &other) {
        reset();
        controlBlock = other.controlBlock;
        if (controlBlock != nullptr) {
            ++controlBlock -> weakCount;
            ++other.controlBlock -> weakCount;
        }
    }
    return *this;
}

template <typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& sharedPtr)
    : controlBlock{sharedPtr.controlBlock}
{
    if (controlBlock != nullptr) {
        ++controlBlock->weakCount;
    }
}

template <typename T>
WeakPtr<T>::~WeakPtr() {
    reset();
}

template <typename T>
SharedPtr<T> WeakPtr<T>::lock() const {
    if (expired()) {
        return SharedPtr<T>();
    }
    return SharedPtr<T>(*this);
}

template <typename T>
bool WeakPtr<T>::expired() const {
    if (controlBlock != nullptr) {
        return controlBlock -> sharedCount == 0;
    }
    return true;
}

template <typename T>
void WeakPtr<T>::reset() {
    --controlBlock -> weakCount;
    if (controlBlock != nullptr) {
        delete controlBlock;
    }
}