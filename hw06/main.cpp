#include <iostream>
#include <list>
#include <array>

class Matrix

{
private:
    std::array<int, 2> addr;
    bool root;
    int level;
    int data;
    std::list<Matrix> child;
    /* data */
public:
    Matrix() : root(true) {};
    Matrix(std::array<int, 2> _addr, int level, int index);
    ~Matrix();
    Matrix &operator[](std::size_t index)
    {
        if (root)
            return child.emplace_back(addr, 0, index);
        else
            return child.emplace_back(addr, level + 1, index);
    }
    Matrix &operator=(int val)
    {
        data = val;

        std::cout << "addr";
        for (size_t i = 0; i < addr.size(); i++)
            std::cout << "[" << addr[i] << "]";
        std::cout << " operator=" << val << std::endl;
        return *this;
    }
};

Matrix ::Matrix(std::array<int, 2> _addr, int level, int index) : addr(_addr), level(level), data(0)
{
    root = false;
    addr[level] = index;
}

Matrix ::~Matrix()
{
}

int main()
{

    Matrix m;
    m[4][2] = 42;
}