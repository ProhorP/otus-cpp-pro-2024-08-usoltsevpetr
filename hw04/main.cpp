#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <array>
#include <type_traits>

// requires std::string<T>
template <typename T,
          std::enable_if_t<std::is_same_v<T, std::string>, bool> = true>
void print_ip(T string)
{
    std::cout << "print_ip_String:" << std::endl;
    std::cout << string << std::endl;
}

// requires std::integral<T>
template <typename T,
          std::enable_if_t<std::is_integral_v<T>, bool> = true>
void print_ip(T param)
{
    // P.S. я в курсе про разный порядок байт на разных архитектурах
    // в качестве простого примера это работает на x86
    union
    {
        T valueIntegral;
        char valueChar[sizeof(T)];
    } u;
    u.valueIntegral = param;
    std::cout << "print_ip_integer:" << std::endl;
    for (ssize_t i = sizeof(u.valueChar) - 1; i >= 0; i--)
    {
        std::size_t tmp = static_cast<uint8_t>(u.valueChar[i]);
        if (i == sizeof(u.valueChar) - 1)
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
    std::cout << "print_ip_Container:" << std::endl;
    std::cout << std::endl;
    auto it = param.begin();
    for (size_t i = 0; it != param.end(); i++)
    {
        if (i == 0)
            std::cout << *it;
        else
            std::cout << '.' << *it;
        ++it;
    }

    std::cout << std::endl;
}

template <std::size_t I = 0, typename... Tp>
inline typename std::enable_if_t<I == sizeof...(Tp), void>
print_tuple([[maybe_unused]] std::tuple<Tp...> &t)
{
}

template <std::size_t I = 0, typename... Tp>
    inline typename std::enable_if_t < I<sizeof...(Tp), void>
                                       print_tuple(std::tuple<Tp...> &t)
{
    if (I < sizeof...(Tp) - 1)
        std::cout << std::get<I>(t) << '.';
    else
        std::cout << std::get<I>(t);
    print_tuple<I + 1, Tp...>(t);
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
void print_ip(T tp)
{
    std::cout << "print_ip_tuple:" << std::endl;
    print_tuple(tp);

    std::cout << std::endl;
}

int main()
{
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
    std::list list{1, 2, 3};

    print_ip(int32_t{2130706433});
    std::string str("assddsd");
    print_ip(str);
    print_ip(vec);
    print_ip(list);
    print_ip(tp);

    print_ip(int8_t{-1});                           // 255
    print_ip(int16_t{0});                           // 0.0
    print_ip(int32_t{2130706433});                  // 127.0.0.1
    print_ip(int64_t{8875824491850138409});         // 123.45.67.89.101.112.131.41
    print_ip(std::string{"Hello, World !"});        // Hello, World!
    print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
    print_ip(std::list<short>{400, 300, 200, 100}); // 400.300.200.100
    print_ip(std::make_tuple(123, 456, 789, 0));    // 123.456.789.0
}