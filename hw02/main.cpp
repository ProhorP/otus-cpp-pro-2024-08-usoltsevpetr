#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "IpV4.h"
#include <algorithm>
#include <fstream>

int main()
{
    try
    {
        std::vector<IpV4> ip_pool;
        // std::ifstream in_file{"/home/user/otus-cpp-pro-2024-08-usoltsevpetr/hw02/ip_filter.tsv"};

        for (std::string line; std::getline(std::cin, line);)
        // for (std::string line; std::getline(in_file, line);)
        {
            ip_pool.emplace_back(line.substr(0, line.find_first_of('\t')));
        }

        std::sort(ip_pool.begin(), ip_pool.end(), IpV4::greater);

        std::for_each(ip_pool.begin(), ip_pool.end(), [](auto ip)
                      { std::cout << ip.getString() << std::endl; });

        // // filter 1
        std::for_each(ip_pool.begin(), ip_pool.end(), [](auto ip)
                      {
                        if (ip.getValue(0) == 1)
                            std::cout << ip.getString() << std::endl; });

        // filter 46, 70
        std::for_each(ip_pool.begin(), ip_pool.end(), [](auto ip)
                      {
                        if (ip.getValue(0) == 46 && ip.getValue(1) == 70)
                            std::cout << ip.getString() << std::endl; });

        // filter any 46
        std::for_each(ip_pool.begin(), ip_pool.end(), [](auto ip)
                      { 
                        if (ip.getValue(0) == 46 ||
                            ip.getValue(1) == 46 ||
                            ip.getValue(2) == 46 ||
                            ip.getValue(3) == 46)
                                std::cout << ip.getString() << std::endl; });
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    // не обязателен в C++
    //  return 0;
}
