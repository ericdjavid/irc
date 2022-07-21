#include <string>
#include <sstream>

template<typename T>
T FromString(const std::string& str)
{
    std::istringstream ss(str);
    T ret;
    ss >> ret;
    return ret;
}