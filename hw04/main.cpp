#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

// requires std::string<T>
template <typename T,
          std::enable_if_t<std::is_same_v<T, std::string>, bool> = true>
void print_ip(T param)
{
    std::cout << "print_ip_String:" << param << std::endl;
}

// requires std::integral<T>
template <typename T,
          std::enable_if_t<std::is_integral_v<T>, bool> = true>
void print_ip(T param)
{
    std::cout << "print_ip_integer:" << param << std::endl;
}

// requires std::container<T>
template <typename T,
          std::enable_if_t<std::is_same_v<decltype(std::declval<T>().emplace_back()), decltype(std::declval<T>().emplace_back())>, bool> = true>
void print_ip(T param)
{
    std::cout << "print_ip_Container:" << std::endl;
    for (auto &i : param)
    {
        std::cout << i << std::endl;
    }
}

int main()
{
    std::string str{"AAA"};
    std::vector vec{1,2,3};

    print_ip(555);
    print_ip(str);
    print_ip(vec);
}