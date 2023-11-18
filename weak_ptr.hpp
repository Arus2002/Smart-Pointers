#ifndef WEAK_PTR_HPP
#define WEAK_PTR_HPP

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
    WeakPtr(WeakPtr&& other);
    WeakPtr& operator=(WeakPtr&& other);
    WeakPtr& operator=(const WeakPtr& other);
    SharedPtr<T> lock() const;
    bool expired() const;
    void reset();
    friend class SharedPtr<T>;

private:
    ControlBlock<T>* controlBlock;
};

#include "weak_ptr.impl.cpp"

#endif