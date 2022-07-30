#pragma once

#include <string>
#include <iostream>
#include "channel.hpp"

class User 
{
	private:
    	int		_id;
		bool		_is_operat;
		std::string	_nick;
		std::string	_username;
		std::string	_last_command;
		std::string	_message_received;
		std::string	_pass;
		Channel		*_current;

	public:
    	User(int id, std::string nick, std::string User) : _id(id), _nick(nick), _username(User)
    	{
       		_is_operat = false;
			_pass = "";
			_last_command = "";
			_message_received = "";
			_current = NULL;
	        	std::cout << "new User created of id : " << _id << std::endl;
		};

		~User() {};
    
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

		void	connect_to_channel(Channel *chann)
		{
			_current = chann;
		}
};