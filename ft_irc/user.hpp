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
		std::string tmp;
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

std::string						get_user_name_2(int id, std::vector<User> tab)
{
	std::vector<User>::iterator	it = tab.begin();
	while(it != tab.end())
	{
		if(it->get_id() == id)
			return (it->get_username());
		it++;
	}
	return ("/*,\\not_in_channel");
}

