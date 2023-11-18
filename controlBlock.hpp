#ifndef CONTROLBLOCK_HPP
#define CONTROLBLOCK_HPP

#include <iostream>

template <typename T>
struct ControlBlock {
    T* m_ptr;
    std::size_t sharedCount = 0;
    std::size_t weakCount = 0;
    ControlBlock(T* ptr)
        : m_ptr(ptr) {}
};

#endif