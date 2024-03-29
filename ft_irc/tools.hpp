#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "user.hpp"
#include <sstream>
#include "debug.hpp"

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
    if (debug)
        std::cout << "||THEPRINT:|" << the_print << "||" << std::endl;
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
        if (debug)
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

void client_printer_channel(int sd, std::string str, User *user, std::string channel_name)
{
    std::string the_print = ":" + user->get_nick() + "!~" + user->get_username() + "@localhost PRIVMSG " + channel_name + " :" + str + "\r\n";
    // the_print = "PRIVMSG " + channel_name + " " + str + "\r\n";
    if (debug)
        std::cout << "Printing: |" << the_print << "|" << std::endl;
    // Allocate memory
    char *ccx = new char[the_print.length() + 1];
    // Copy contents
    std::copy(the_print.begin(), the_print.end(), ccx);
    if (send(sd, ccx, the_print.size(), 0) != (ssize_t)the_print.size())
        perror("send");
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

void display_users(std::vector<User> the_users)
{
    std::vector<User>::iterator it;

    it = the_users.begin();
    if (debug)
        std::cout << C_YELLOW << "||||||||||||| USERS |||||||||||||" << C_END;
    while (it != the_users.end())
    {
        if (debug)
            std::cout << "id : " << it->get_id() << " | nick : " << it->get_nick() << " | username : " << it->get_username() << std::endl;
        it++;
    }
    if (debug)
        std::cout << C_YELLOW << "||||||||||||| END |||||||||||||" << std::endl << C_END;
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

// RETURN 1 IF WRONG AND 0 IF OK
int check_partial_cmd(std::string cmd, int size)
{
    if (cmd.size() == (size_t)size)
    {
        if (debug)
            std::cout << "Wrong or partial command =(" << std::endl;
        return 1;
    }
    return 0;
}

void    send_kick_to_channel(std::string msg, std::vector<User> *tab)
{
    std::vector<User>::iterator it;
    it = tab->begin();
    while (it != tab->end())
    {
        send(it->get_id(), msg.c_str(), msg.length(), 0);
        it++;
    }
}