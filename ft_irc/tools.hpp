#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

template<typename T>
T FromString(const std::string& str)
{
    std::istringstream ss(str);
    T ret = 0; 
    ss >> ret;
    return ret;
}

void error(std::string str)
{
    std::cout << str << std::endl;
    exit(EXIT_FAILURE);
};

void tokenize(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

void get_buffer(char *buff)
{
    std::ofstream myfile;
    myfile.open ("buffer.txt", std::ios::app);
    myfile << buff;
    myfile.close();
}

// Function to compare strings and return true if it matches
bool ft_compare_tokens(std::string token, int jump, std::string expected)
{
    if (expected.compare(token.substr(jump, token.length())))
        return true;
    return false;
}
