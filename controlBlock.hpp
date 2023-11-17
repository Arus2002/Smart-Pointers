#ifndef CONTROLBLOCK_HPP
#define CONTROLBLOCK_HPP

#include <iostream>

template <typename T>
struct ControlBlock {
    T* m_ptr;
    static std::size_t sharedCount;
    static std::size_t weakCount;
};

template <typename T>
std::size_t ControlBlock<T>::sharedCount = 0;

template <typename T>
std::size_t ControlBlock<T>::weakCount = 0;

#endif