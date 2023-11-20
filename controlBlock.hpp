#ifndef CONTROLBLOCK_HPP
#define CONTROLBLOCK_HPP

#include <iostream>

template <typename T>
struct ControlBlock {
    T* m_ptr;
    std::size_t sharedCount = 0;
    std::size_t weakCount = 0;
    ControlBlock(T* ptr);
    ControlBlock(const ControlBlock& rhs);
    ControlBlock& operator=(const ControlBlock& rhs);
    ~ControlBlock();
};

#include "controlBlock.impl.cpp"

#endif