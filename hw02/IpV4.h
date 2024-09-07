#include <string>
#include <array>
#include <sstream>

class IpV4
{
public:
    IpV4() = default;
    IpV4(std::string stringParam) : string{stringParam} {};
    static bool compareGreater(const IpV4 &lhs, const IpV4 &rhs);
    ~IpV4();

private:
    std::string string;
    std::array<int, 4> data;
};

IpV4::IpV4(std::string stringParam) : string{stringParam}
{

    std::string segment;
    std::stringstream ss(stringParam);
    int i = 0;

    // Разделяем строку по символу '.'
    while (std::getline(ss, segment, '.') && i < 4)
    {
        data[i] = std::stoi(segment);
        i++;
    }
}

bool IpV4::compareGreater(const IpV4 &lhs, const IpV4 &rhs) 
{
    for (size_t i = 0; i < 4; i++){
        if (lhs.data[i] > rhs.data[i])
            return true;
        if (lhs.data[i] < rhs.data[i])
            return false;
    }
    return false;
}

IpV4::~IpV4()
{
}
