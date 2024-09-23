#include <cstddef>
#include <memory>
#include <list>

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

    // std::shared_ptr<void> pool;
    std::shared_ptr<std::list<std::shared_ptr<void>>> poolList;
    std::size_t poolSize = 10;
    std::size_t pos;

    cpp_11_allocator() noexcept
        : 
        // pool(::operator new(sizeof(T) * 10), deleter()),
          poolList(std::make_shared<std::list<std::shared_ptr<void>>>())
    {
        poolList->emplace_back(::operator new(sizeof(T) * 10), deleter());
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
            poolList->emplace_back(::operator new(sizeof(T) * poolSize), deleter());
            pos = 0;
        }
        // if (pos + n > poolSize)
        //     throw std::bad_alloc();

        int cur = pos;
        pos += n;
        // T *ret = reinterpret_cast<T *>(pool.get()) + cur;
        T *ret = reinterpret_cast<T *>(poolList->back().get()) + cur;
        return ret;
    }
    void deallocate(T *p, std::size_t n)
    {
        // implementation
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