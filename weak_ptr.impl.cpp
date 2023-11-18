#include "weak_ptr.hpp"

template <typename T>
WeakPtr<T>::WeakPtr() : controlBlock(nullptr) {}

template <typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& sharedPtr)
    : controlBlock{sharedPtr.controlBlock} 
{
    if (controlBlock != nullptr) {
        ++controlBlock -> weakCount;
        std::cout << controlBlock -> sharedCount << std::endl;
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
        return SharedPtr<T>();
    }
    return SharedPtr<T>(*this);
}

template <typename T>
bool WeakPtr<T>::expired() const {
    if (controlBlock != nullptr) {
        return controlBlock == nullptr || controlBlock -> sharedCount == 0;
    }
    return false;
}

template <typename T>
void WeakPtr<T>::reset() {
    --controlBlock -> weakCount;
    if (controlBlock != nullptr) {
        delete controlBlock;
    }
}