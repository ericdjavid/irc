#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>

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

std::vector<std::string> split (std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    //PBM DS SPLIT, SPLIT PAS TOUT LES ESPACES 
    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }
    res.push_back (s.substr (pos_start));
    return res;
}


void get_buffer(char *buff)
{
    std::ofstream myfile;
    myfile.open ("buffer.txt", std::ios::app);
    myfile << buff;
    myfile.close();

}