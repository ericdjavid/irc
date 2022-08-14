#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "user.hpp"
#include <sstream>

template <typename T>
T FromString(const std::string &str)
{
    std::istringstream ss(str);
    T ret = 0;
    ss >> ret;
    return ret;
}

std::string to_str(int k)
{
    std::stringstream ss;
    ss << k;
    std::string s;
    ss >> s;
    std::cout << "String representation of an integer value is : " << s;
    return (s);
}

// RETURN INDEX OF VECTOR OR -1 IF NOT FOUND
int check_vector_arr(std::vector<std::string> buff_arr, std::string target)
{
    int i = 0;
    for (std::vector<std::string>::iterator it = buff_arr.begin(); it != buff_arr.end(); ++it)
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
    myfile.open("buffer.txt", std::ios::app);
    myfile << buff;
    myfile << "-----\n";
    myfile.close();
}

void client_printer(int sd, std::string str, std::string numeric, std::string user)
{
    std::string beg(":localhost ");
    std::string the_print;
    if (numeric == "0")
        the_print = str + "\r\n";
    else
        the_print = beg + numeric + " " + user + " :" + str + "\r\n";
    // Allocate memory
    char *ccx = new char[the_print.length() + 1];
    // Copy contents
    std::copy(the_print.begin(), the_print.end(), ccx);
    if (send(sd, ccx, the_print.size(), 0) != (ssize_t)the_print.size())
    {
        perror("send");
    }
    delete[] ccx;
    return;
}

void ultimate_printer(int sd, std::string str, std::string numeric, std::string user)
{
    std::string beg(":localhost ");
    std::string the_print;
    if (numeric == "0")
        the_print = str + "\r\n";
    else
        the_print = beg + numeric + " " + user + str + "\r\n";
    // Allocate memory
    char *ccx = new char[the_print.length() + 1];
    // Copy contents
    // std::cout << "||THEPRINT:|" << the_print << "||" << std::endl;
    std::copy(the_print.begin(), the_print.end(), ccx);
    if (send(sd, ccx, the_print.size(), 0) != (ssize_t)the_print.size())
    {
        perror("send");
    }
    delete[] ccx;
    return;
}

void client_printer2(int fd, class User *us, std::string str, std::string numeric, std::string target)
{
    std::string beg(":" + us->get_nick() + "!~" + us->get_username() + "@localhost ");
    std::string the_print;
    if (numeric == "0")
    {
        std::cout << "Numeric is 0" << std::endl;
        the_print = beg + str + "\r\n";
    }
    else
        the_print = beg + numeric + " " + target + " :" + str + "\r\n";
    std::cout << "Message sent to client is: |" << the_print << "|" << std::endl;

    if (send(fd, the_print.c_str(), the_print.length(), 0) == -1)
    {
        std::cout << "Problem with join send" << std::endl;
    }
    return;
}

void client_printer_channel(int sd, std::string str, std::string numeric, std::string user, std::string channel_name)
{
    (void)numeric;
    (void)user;
    std::string the_print;
    the_print = "PRIVMSG " + channel_name + " " + str + "\r\n";
    std::cout << "Printing: |" << the_print << "|" << std::endl;
    // Allocate memory
    char *ccx = new char[the_print.length() + 1];
    // Copy contents
    std::copy(the_print.begin(), the_print.end(), ccx);
    if (send(sd, ccx, the_print.size(), 0) != (ssize_t)the_print.size())
    {
        perror("send");
    }
    delete[] ccx;
    return;
}

void print_vector(std::vector<std::string> buff_arr)
{
    int i = 0;
    for (std::vector<std::string>::iterator it = buff_arr.begin(); it != buff_arr.end(); ++it)
    {
        std::cout << "vector[" << i << "] = ";
        std::cout << *it << std::endl;
        i++;
    }
}

// RETURN 1 IF YES AND 0 IF NO
int nick_already_in_use(std::string nick, std::vector<User> vector)
{
    std::vector<User>::iterator it;

    if (vector.empty())
        return (0);
    it = vector.begin();
    while (it != vector.end())
    {
        std::cout << "CHECK IF NICK ALREADY USED" << std::endl;
        std::cout << "Comparing " << it->get_nick() << " with " << nick << std::endl;
        if (it->get_nick() == nick)
            return (1);
        it++;
    }
    return (0);
}

int id_already_in_use(int id, std::vector<User> vector)
{
    std::vector<User>::iterator it;

    if (vector.empty())
        return (0);
    it = vector.begin();
    while (it != vector.end())
    {
        if (it->get_id() == id)
            return (1);
        it++;
    }
    return (0);
}

class User *create_new_user(int id, std::string nick, std::string username, std::vector<User> *tab)
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
    std::cout << "||||||||||||| USERS |||||||||||||" << std::endl;
    while (it != the_users.end())
    {
        std::cout << "id : " << it->get_id() << " | nick : " << it->get_nick() << " | username : " << it->get_username() << std::endl;
        it++;
    }
    std::cout << "||||||||||||| END |||||||||||||" << std::endl;
}

int check_if_many_user(std::string target)
{
    int i = 0;
    for (size_t size = 0; size < target.size(); size++)
        if (target[size] == ';' || target[size] == '|')
            i++;
    return (i + 1);
}

std::vector<std::string> get_everyone(std::string target, int i)
{
    std::vector<std::string> targets;
    std::string test;
    std::string needle("|");
    std::string needle1(";");
    size_t found1;
    size_t found2;

    std::cout << target << std::endl;
    size_t start = 0;
    while (i > 0)
    {
        found1 = target.find(needle);
        found2 = target.find(needle1);
        if (found1 > found2)
            test = target.substr(0, found2);
        else
            test = target.substr(0, found1);
        start = test.size();
        target = target.erase(0, start + 1);
        targets.push_back(test);
        i--;
    }
    return (targets);
}

int check_partial_cmd(std::string cmd, int size)
{
    if (cmd.size() == (size_t)size)
    {
        std::cout << "Wrong or partial command =(" << std::endl;
        return 1;
    }
    return 0;
}