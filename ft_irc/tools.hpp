#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "user.hpp"

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
    myfile << "-----\n"; 
    myfile.close();
}

void client_printer(int sd, char const *str, int numeric, std::string user)
{   
    std::string the_str(str);
    std::stringstream ss;
    ss << numeric;
    std::string num = ss.str();
    std::string the_print = ":localhost " + num + " " + user + " :" + the_str + "\r\n";
    std::cout << the_print << std::endl;
    // Allocate memory
    char *ccx = new char[the_print.length() + 1];
    // Copy contents
    std::copy(the_print.begin(), the_print.end(), ccx);
    if (send(sd , ccx, the_print.size() , 0 ) != (ssize_t)the_print.size())
    {
        perror("send");
    }
    delete[] ccx;
    return ;
}

void print_vector(std::vector<std::string> buff_arr)
{
    int i = 0;
    for (std::vector<std::string>::iterator it = buff_arr.begin() ; it != buff_arr.end() ; ++it)
    {
        std::cout << "vector[" << i << "] = ";
        std::cout << *it << std::endl;
        i++;
    }
}

int nick_already_in_use(std::string nick, std::vector<User> vector)
{
    std::vector<User>::iterator it;

    it = vector.begin();
    while (it != vector.end())
    {
        if (it->get_nick() == nick)
            return (1);
        it++;
    }
    if (vector.size() > 0 && it->get_nick() == nick)
    {
        std::cout << "only one user and nick is " << it->get_nick() << std::endl;
        return (1);
    }
    return (0);
}

// void display_users(std::vector<User> the_users)
// {


// }

		// class User	create_new_user(int id, std::string nick, std::string username, std::vector<User> *tab)
		// {
		// 	if (nick_already_in_use(nick, tab->the_users))
		// 	{

		// 	}
		// }