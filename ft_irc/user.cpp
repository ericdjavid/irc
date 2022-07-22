#include "user.hpp"

int user::set_nick(std::string nick)
{
    _nick = nick;
    return 1;
};

int user::set_password(std::string pswd)
{
    _password = pswd;
    return 1;
};

int user()
{
	int	user;
	char	buffer[1024];
	//char	ip[] = "127.0.0.1";

	struct sockaddr_in	user_addr;

	user = socket(AF_INET, SOCK_STREAM, 0);
	if (user < 0)
	{
		std::cout << "socket user failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "User socket has been created" << std::endl;
	user_addr.sin_family = AF_INET;
	user_addr.sin_port = htons(1234);

	if (connect(user, (struct sockaddr *)&user_addr, sizeof(user_addr)) == 0)
		std::cout << "Connection to the server port number: " << std::endl;

	recv(user, buffer, 1024, 0);
	std::cout << "Connexion confirmed, you are good to go .." << std::endl;

	do
	{
		std::cout << "User: ";
		do
		{
			std::cin >> buffer;
			send(user, buffer, 1024, 0);
		}
	while (*buffer != 42);
	}
	while (*buffer != 42);
	close(user);
	return (0);
}
