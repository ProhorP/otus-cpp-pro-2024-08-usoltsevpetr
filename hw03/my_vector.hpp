// #include "cpp_11_allocator.hpp"
#include <memory>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <map>

template <class T, class Allocator = std::allocator<T>>
class my_vector
{
public:
    void push_back(const T &x)
    {
        if (capacity == 0)
        {
            capacity = 10;
            data = std::allocator_traits<Allocator>::allocate(alloc, capacity);
        }
        if (curSize == capacity)
        {
            capacity = capacity * 2 + 1;
            T *newData = std::allocator_traits<Allocator>::allocate(alloc, capacity);
            std::copy(data, data + curSize, newData); // naive
            std::swap(newData, data);
            std::allocator_traits<Allocator>::deallocate(alloc, newData, curSize);
        }

        std::allocator_traits<Allocator>::construct(alloc, data + curSize, x);
        ++curSize;
    }

    std::size_t size() const
    {
        return curSize;
    };

    T &operator[](std::size_t pos) const
    {
        return data[pos];
    };

    struct iterator
    {
    public:
        explicit iterator(T *ptr) : ptr{ptr} {};

        iterator &operator++()
        {
            ptr++;
            return *this;
        }

        bool operator!=(const iterator &other)
        {
            return ptr != other.ptr;
        }

        T &operator*()
        {
            return get();
        }

        T &get()
        {
            return *ptr;
        }

    private:
        T *ptr;
    };

    iterator begin() const
    {
        return iterator(data);
    }

    iterator end() const
    {
        return iterator(data + curSize);
    }

    ~my_vector() {
    };

private:
    std::size_t curSize = 0;
    std::size_t capacity = 0;
    T *data = nullptr;

    Allocator alloc;
};