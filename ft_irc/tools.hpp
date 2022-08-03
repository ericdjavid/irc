#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "user.hpp"

template<typename T>
T FromString(const std::string& str)
{
    std::istringstream ss(str);
    T ret = 0; 
    ss >> ret;
    return ret;
}

int check_vector_arr(std::vector<std::string> buff_arr, std::string target)
{
	int i = 0;
	for (std::vector<std::string>::iterator it = buff_arr.begin() ; it != buff_arr.end() ; ++it)
	{
		i++;
		size_t s = target.length();
		std::string new_str(*it);
		new_str = new_str.substr(0, s);
		// std::cout << "comparing:";
		// std::cout << new_str;
		// std::cout << " with:";
		// std::cout << target << std::endl;
		if (new_str.compare(target) == 0)
		{
			// int index = std::distance(buff_arr.begin(), it);
			return i;
		}
	}
	return -1;
}

void error(std::string str)
{
    std::cout << str << std::endl;
    exit(EXIT_FAILURE);
};

void tokenize(std::string &str, const char delim,
            std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;
    str.erase(remove(str.begin(), str.end(), '\r'), str.end());
 
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

void client_printer(int sd, std::string str, std::string numeric, std::string user)
{   
    std::string beg(":localhost ");
    std::string the_print;
    if (numeric == "0")
        the_print = str + "\n";
    else
        the_print = beg + numeric + " " + user + ": " + str + "\n";
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
        return (1);
    return (0);
}

class User	*create_new_user(int id, std::string nick, std::string username, std::vector<User> *tab)
{
	if (nick_already_in_use(nick, *tab))
	{
        std::cout << "Nick already in use, please choose another one." << std::endl;
        return NULL;
	}
    class User *new_one = new User(id, nick, username);
    return new_one;
}

void display_users(std::vector<User> the_users)
{
    std::vector<User>::iterator it;

    it = the_users.begin();
    while (it != the_users.end())
    {
        std::cout << "id : " << it->get_id() << " | nick : " << it->get_nick() << " | username : " << it->get_username() << std::endl;
        it++;
    }
}