#include "controlBlock.hpp"

template <typename T>
ControlBlock<T>::ControlBlock(T* ptr)
    : m_ptr(ptr) {}

template <typename T>
ControlBlock<T>::~ControlBlock() {
    delete m_ptr;
}