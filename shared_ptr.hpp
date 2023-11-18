#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include "controlBlock.hpp"

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
public:
    SharedPtr();
    explicit SharedPtr(T value);
    explicit SharedPtr(T* ptr);
    SharedPtr(const SharedPtr& rhs);
    SharedPtr(SharedPtr&& rhs);
    SharedPtr& operator=(SharedPtr&& rhs);
    SharedPtr& operator=(const SharedPtr& rhs);
    T& operator*() const;
    T* operator->() const;
    T* get() const;
    void reset();
    void swap(SharedPtr& rhs);
    std::size_t use_count() const;
    bool unique() const;
    ~SharedPtr();
    friend class WeakPtr<T>;
    
private:
    ControlBlock<T>* controlBlock;

private:
    SharedPtr(const WeakPtr<T>& weakPtr);
};

#include "shared_ptr.impl.cpp"

#endif