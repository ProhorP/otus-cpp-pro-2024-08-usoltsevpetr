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
    void print() const
    {
        std::cout << "addr";
        for (size_t i = 0; i < addr.size(); i++)
            std::cout << "[" << addr[i] << "]";
        std::cout << " data=" << data << std::endl;
    }
    Matrix &operator=(int val)
    {
        data = val;

        print();
        return *this;
    }

    struct iterator
    {
    public:
        explicit iterator(Matrix *ptr) : ptr{ptr}, level{0}
        {
            if (ptr)
            {
                iters[level].first = ptr->child.begin();
                iters[level].second = ptr->child.end();
                rewind();
            }
        };
        iterator &operator++()
        {

            // на самом глубоком уровне переключаемся на след элемент списка
            // если мы достигли конца списка, то переходим на уровень выше и повторяем снова
            while (++iters[level].first == iters[level].second)
                if (--level < 0)
                {
                    // если выше нет итераторов - зануляем текущий указатель на матрицу
                    // что будет значить конец итератора в рамках всей матрицы
                    ptr = nullptr;
                    return *this;
                }

            // Если мы переключались на уровни выше, то находим первый элемент от текущего уровня
            if (level != 2 - 1)
                rewind();

            return *this;
        }
        void rewind()
        {
            while (iters[level].first->child.begin() != iters[level].first->child.end())
            {
                iters[level + 1].first = iters[level].first->child.begin();
                iters[level + 1].second = iters[level].first->child.end();
                level++;
            }
        }
        bool operator!=(const iterator &other)
        {
            return ptr != other.ptr;
        }

        Matrix &operator*()
        {
            return get();
        }

        Matrix &get()
        {
            if (level == 2 - 1)
                return *iters[level].first;
            else
                throw "нарушена глубина матрицы";
        }

    private:
        Matrix *ptr;
        //массив пар итераторов(текущий итератор и конец)
        //размер массива = N-мерности матрицы
        std::array<std::pair<std::list<Matrix>::iterator,std::list<Matrix>::iterator>, 2> iters;
        int level;
    };

    iterator begin()
    {
        return iterator(this);
    }

    iterator end() const
    {
        return iterator(nullptr);
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
    m[5][7] = 57;

    for (auto &tmp : m)
    {
        tmp.print();
    }
}