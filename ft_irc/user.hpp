#pragma once

#include <string>
#include <iostream>
#include "tools.hpp"

typedef class User 
{
	private:
		int			_id;
		bool		_is_operat;
		std::string	_nick;
		std::string	_username;
		std::string	_last_command;
		std::string	_message_received;
		bool		_set_nick;

	public:
    	User(int id, std::string nick, std::string User)
    	{
			_id = id;
			_nick = nick;
			_username = User;
       		_is_operat = false;
			_set_nick = true;
		};
    	User(int id)
    	{
			_id = id;
			_nick = "none";
			_username = "none";
       		_is_operat = false;
			_set_nick = false;
		};

		User() {};

		~User() {};

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

		int		get_id(void)
		{
			return (_id);
		}

		void	set_the_nick(std::string nick)
    	{
    		_nick = nick;
    	};

		std::string	get_nick(void)
		{
			return (_nick);
		}
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

		std::string	get_username(void)
		{
			return (_username);
		}

		void	set_operat(bool n)
		{
			_is_operat = n;
		}

		void	set_nick(bool n)
		{
			_set_nick = n;
		}

		bool	get_set_nick(void)
		{
			return (_set_nick);
		}
} User;
    		void	set_pass(std::string pswd)
    		{
    			_pass = pswd;
    		};

		void	connect_to_channel(Channel chann)
		{
			_current = chann;
		}
};

User							get_user_to_delete(int id, std::vector<User> tab)
{
	std::vector<User>::iterator	it = tab.begin();
	while(it != tab.end())
	{
		if(it->get_id() == id)
			return (*it);
		it++;
	}
	return (*it);
}

std::vector<User>::iterator		get_user_position(int id, std::vector<User> tab)
{
	std::vector<User>::iterator	it = tab.begin();
	while(it != tab.end())
	{
		if(it->get_id() == id)
			return (it);
		it++;
	}
	return (it);
}

std::string						get_user_name(int id, std::vector<User> tab)
{
	std::vector<User>::iterator	it = tab.begin();
	while(it != tab.end())
	{
		if(it->get_id() == id)
			return (it->get_nick());
		it++;
	}
	return ("/*,\\not_in_channel");
}

std::string						get_response_1(int	id, std::vector<User> tab, std::string command_name)
{
	std::vector<User>::iterator	it = tab.begin();
	std::string					response;
	while(it != tab.end())
	{
		if(it->get_id() == id)
		{
			std::cout << "GET RESPONSE : |" << it->get_nick() << "| |" << it->get_username() << "|" << std::endl;
			response = ":" + it->get_nick() + "!~" + it->get_username() + "@localhost " + command_name;
			break ;
		}
		it++;
	}
	return (response);
}