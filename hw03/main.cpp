#include "cpp_11_allocator.hpp"
#include "my_vector.hpp"
#include <map>
#include <iostream>

int main()
{

    // int count = 10;

    // //container1
    // std::map<int, int> container1;
    // for (int i = 0; i < count; i++)
    //     container1[i] = i;

    // std::cout << "container1:" << std::endl;
    // for (auto &i : container1)
    //     std::cout << "[" << i.first << "] = " << i.second << std::endl;

    // //container2
    // std::map<int, int, std::less<int>, cpp_11_allocator<std::pair<const int, int>>> container2;
    // for (int i = 0; i < count; i++)
    //     container2[i] = i;

    // std::cout << std::endl
    //           << "container2:" << std::endl;
    // for (auto &i : container2)
    //     std::cout << "[" << i.first << "] = " << i.second << std::endl;

    // //container3
    // my_vector<int> container3;
    // for (int i = 0; i < count; i++)
    //     container3.push_back(i);

    // std::cout << std::endl
    //           << "container3:" << std::endl;
    // for (std::size_t i = 0; i < container3.size(); i++)
    //     std::cout << "[" << i << "] = " << container3[i] << std::endl;

    //container4
    my_vector<int, cpp_11_allocator<int>> container4;
    for (int i = 0; i < 20; i++)
        container4.push_back(i);

    std::cout << std::endl
              << "container4:" << std::endl;
    for (std::size_t i = 0; i < container4.size(); i++)
        std::cout << "[" << i << "] = " << container4[i] << std::endl;

}