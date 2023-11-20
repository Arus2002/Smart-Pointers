#include "controlBlock.hpp"

template <typename T>
ControlBlock<T>::ControlBlock(T* ptr)
    : m_ptr(ptr)
    , sharedCount{0}
    , weakCount{0} {}

template <typename T>
ControlBlock<T>::~ControlBlock() {
    delete m_ptr;
}

template <typename T>
ControlBlock<T>::ControlBlock(const ControlBlock& rhs)
    : m_ptr{rhs.m_ptr}
    , sharedCount{rhs.sharedCount}
    , weakCount{rhs.weakCount} {}

template <typename T>
ControlBlock<T>& ControlBlock<T>::operator=(const ControlBlock& rhs) {
    m_ptr = rhs.m_ptr;
    sharedCount = rhs.sharedCount;
    weakCount = rhs.weakCount;
}