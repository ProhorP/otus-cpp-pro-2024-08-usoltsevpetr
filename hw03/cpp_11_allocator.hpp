#include <cstddef>
#include <memory>
#include <list>
#include <iostream>
#include "wrapped_mem.h"

struct deleter
{
    void operator()(void *ptr)
    {
        ::operator delete(ptr);
    }
};

template <class T>
struct cpp_11_allocator
{
    using value_type = T;

    std::shared_ptr<std::list<std::shared_ptr<wrapped_mem>>> poolList;
    std::size_t poolSize = 10;
    std::size_t pos;

    cpp_11_allocator()
        : poolList(std::make_shared<std::list<std::shared_ptr<wrapped_mem>>>())
    {
        poolList->push_back(std::make_shared<wrapped_mem>(10 * sizeof(T)));
    }

    template <class U>
    cpp_11_allocator(const cpp_11_allocator<U> &a) noexcept
    {
        poolList = a.poolList;
        poolSize = a.poolSize;
        pos = a.pos;
    }

    cpp_11_allocator select_on_container_copy_construction() const
    {
        return cpp_11_allocator();
    }

    T *allocate(std::size_t n)
    {
        if (pos + n > poolSize)
        {
            poolSize = pos + n;
            poolList->push_back(std::make_shared<wrapped_mem>(poolSize * sizeof(T)));
            pos = 0;
        }

        int cur = pos;
        pos += n;
        poolList->back()->push();
        // std::cout << "allocate=" << poolList->back()->get() << std::endl;
        return reinterpret_cast<T *>(poolList->back()->get()) + cur;
    }

    void deallocate(T *p, std::size_t n)
    {
        if (n == 0)
            return;
        for (auto &i : *poolList)
        {
            if (p >= (*i).get() && p < (*i).getEnd())
            {
                (*i).pop();
                if ((*i).getCnt() == 0)
                    (*poolList).remove(i);
                return;
            }
        }
    }

    void print()
    {
        for (auto &i : *poolList)
        {
            std::cout << "data=" << (*i).get() << ", size=" << (*i).getSize() << ", cnt=" << (*i).getCnt() << std::endl;
        }
    }

    template <class U>
    struct rebind
    {
        using other = cpp_11_allocator<U>;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type; // UB if std::false_type and a1 != a2;
};

template <class T, class U>
constexpr bool operator==(const cpp_11_allocator<T> &a1, const cpp_11_allocator<U> &a2) noexcept
{
    return a1.pool == a2.pool;
}

template <class T, class U>
constexpr bool operator!=(const cpp_11_allocator<T> &a1, const cpp_11_allocator<U> &a2) noexcept
{
    return a1.pool != a2.pool;
}