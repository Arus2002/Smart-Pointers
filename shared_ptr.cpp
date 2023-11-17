#include <iostream>
#include "controlBlock.hpp"

template <typename T>
class SharedPtr {
public:
    explicit SharedPtr(T value);
    explicit SharedPtr(T* ptr);
    SharedPtr(const SharedPtr& rhs);
    SharedPtr& operator=(const SharedPtr& rhs);
    T& operator*() const;
    T* operator->() const;
    ~SharedPtr();
    
private:
    ControlBlock<T>* controlBlock;
};

template <typename T>
SharedPtr<T>::SharedPtr(T value)
        : controlBlock{new ControlBlock<T>{new T(value)}} {}

template <typename T> 
SharedPtr<T>::SharedPtr(T* ptr)
        : controlBlock{new ControlBlock<T>{ptr}} {}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& rhs)
    : controlBlock{rhs.controlBlock}
{
    ++controlBlock -> sharedCount;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& rhs) {
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
    --controlBlock -> sharedCount;
    if (controlBlock -> sharedCount == 0) {
        delete controlBlock -> m_ptr;
        delete controlBlock;
    }
}
