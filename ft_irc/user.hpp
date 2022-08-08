#pragma once

#include <string>
#include <iostream>
//#include "channel.hpp"
// #include "tools.hpp"

typedef class User 
{
	private:
    	int			_id;
		bool		_is_operat;
		std::string	_nick;
		std::string	_username;
		std::string	_last_command;
		std::string	_message_received;
		std::string	_pass;
	//	Channel		*_current;

	public:
    	User(int id, std::string nick, std::string User)
    	{
			_id = id;
			_nick = nick;
			_username = User;
       		_is_operat = false;
			_pass = "";
			_last_command = "";
			_message_received = "";
	//		_current = NULL;
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

		void	set_last_command(std::string str)
		{
			_last_command = str;
		};

		std::string	get_last_command(void)
		{
			return (_last_command);
		}

		void	set_message_received(std::string str)
		{
			_message_received = str;
		};

		std::string		get_message_received(void)
		{
			return (_message_received);
		}

		void	set_nick(std::string nick)
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

    	void	set_pass(std::string pswd)
    	{
    		_pass = pswd;
    	};

		std::string	get_pass(void)
		{
			return (_pass);
		}
/*
		void	connect_to_channel(Channel *chann)
		{
			_current = chann;
		}

		void	disconnect_from_channel (void)
		{
			_current = NULL;
		}
*/
		void	set_operat(bool n)
		{
			_is_operat = n;
		}

} User;
