#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <array>
#include <type_traits>

// requires std::string<T>
template <typename T,
          std::enable_if_t<std::is_same_v<T, std::string>, bool> = true>
void print_ip(T string)
{
    std::cout << "print_ip_String:";
    std::cout << string << std::endl;
}

// requires std::integral<T>
template <typename T,
          std::enable_if_t<std::is_integral_v<T>, bool> = true>
void print_ip(T param)
{
    //P.S. я в курсе про разный порядок байт на разных архитектурах
    //в качестве простого примера это работает на x86
    union
    {
        T valueIntegral;
        char valueChar[sizeof(T)];
    } u;
    u.valueIntegral = param;
    std::cout << "print_ip_integer:";
    for (ssize_t i = sizeof(u.valueChar)-1; i >= 0; i--)
    {
        std::size_t tmp = static_cast<uint8_t>(u.valueChar[i]);
        if (i == sizeof(u.valueChar)-1)
            std::cout << tmp;
        else
            std::cout << '.' << tmp;
    }
    std::cout << std::endl;
}

// requires std::container<T>
// Если у объекта есть метод emplace_back - значит это контейнер
// std::string не имеет этого метода
template <typename T,
          std::enable_if_t<
              std::is_same_v<
                  decltype(std::declval<T>().emplace_back()),
                  decltype(std::declval<T>().emplace_back())>,
              bool> = true>
void print_ip(T param)
{
    std::cout << "print_ip_Container:";
    std::cout << std::endl;
    for (auto &i : param)
    {
        std::cout << i << std::endl;
    }
}

// requires std::tuple<T>
// получаем тип первого элемента и количество элементов в tuple(T)
// создаем массив на основании этого
// далее массив преобразуем в tuple через tuple_cat и сравниваем с типом T
template <typename T,
          std::enable_if_t<
              std::is_same_v<T,
                             decltype(std::tuple_cat(std::declval<
                                                     std::array<
                                                         std::remove_reference_t<decltype(std::get<0>(std::declval<T>()))>,
                                                         std::tuple_size_v<std::remove_reference_t<decltype(std::declval<T>())>>>>()))>,
              bool> = true>
void print_ip(T param)
{
    std::cout << "print_ip_tuple:";
    std::cout << std::get<0>(param) << std::endl;
}

int main()
{
    std::string str{"AAA"};
    auto tp = std::make_tuple(123, 456, 789, 0);
    std::array<std::remove_reference_t<decltype(std::get<0>(tp))>, std::tuple_size_v<decltype(tp)>> arr;
    auto tp_1 = std::tuple_cat(arr);
    // Проверка типов
    if constexpr (std::is_same_v<decltype(tp), decltype(tp_1)>)
    {
        std::cout << "Типы одинаковы\n";
    }
    else
    {
        std::cout << "Типы различны\n";
    }

    std::cout << std::get<0>(tp_1) << "." << std::get<1>(tp_1) << "." << std::get<2>(tp_1) << "." << std::get<0>(tp_1) << std::endl;

    std::vector vec{1, 2, 3};

    print_ip( int32_t{2130706433});
    print_ip(str);
    print_ip(vec);
    print_ip(tp);
}