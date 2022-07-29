#pragma once

#include <string>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

class user 
{
	private:
    		int		_id;
		bool		_is_operat;
		std::string	_nick;
		std::string	_username;
		std::string	_last_command;
		std::string	_message_received;
		std::string	_pass;
		Channel		_current;

	public:
    		user(int id, std::string nick, std::string user) : _id(id), _nick(nick), _user(user)
    		{
       			_is_operat = false;
			_pass = NULL;
			_last_command = "";
			_message_received = "";
			_current = NULL;
	        	std::cout << "new user created of id : " << _id << std::endl;
		};

		~user() {};
    
		void	set_id(int id)
		{
			_id = id;
		};

		void	set_last_command(std::string str)
		{
			_last_command = str;
		};

		void	set_message_received(std::string str)
		{
			_message_received = str;
		};

		void	set_nick(std::string nick)
    		{
    			_nick = nick;
    		};

		void	set_username(std::string username)
		{
			_username = username;
		}

    		void	set_pass(std::string pswd)
    		{
    			_pass = pswd;
    		};

		void	connect_to_channel(Channel chann)
		{
			_current = chann;
		}
};


