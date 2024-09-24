#include <cstddef>
#include <memory>

class wrapped_mem
{
public:
    wrapped_mem() = default;

    wrapped_mem(std::size_t size) : cnt(0), size(size)
    {
        data = ::operator new(size);
        std::cout << "new=" << data << ", size=" << size << std::endl;
    };
    ~wrapped_mem()
    {
        std::cout << "delete=" << data << std::endl;
        ::operator delete(data);
    };
    void *get() noexcept
    {
        return data;
    }
    void *getEnd() noexcept
    {
        return reinterpret_cast<char *>(data) + size;
    }
    void push() noexcept
    {
        cnt++;
    }
    void pop() noexcept
    {
        cnt--;
    }
    bool empty() const noexcept
    {
        return cnt == 0;
    }

private:
    void *data = nullptr;
    std::size_t cnt = 0;
    std::size_t size = 0;
};
