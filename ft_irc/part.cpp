#include <string>
#include <string.h>
#include <iostream>
#include <vector>

typedef struct 					s_part2
{
	int							nb_chann;
	std::vector<std::string>	channels;
	std::string					channel;
	std::string					reason;
}								t_part2;

void	show_data_parsed_part(t_part2 var)
{
	int         i;
    int         j = 0;

	i = var.nb_chann;
	std::cout << "chann en cours : " << var.channel << std::endl;
    std::cout << "nb chann a quitter : " << var.nb_chann << std::endl;
	while (j < i)
    {
    	std::cout << "chan " << j << " a quitter : " << var.channels.at(j) << std::endl;
        j++;
    }
	std::cout << "reason : " << var.reason << std::endl;
}

t_part2		split_part_command(std::string command)
{
	t_part2		*result = new t_part2;
	std::string		tmp;
	int			i = -1;

	i++;
	tmp = "";
	result->channel = command.substr(0, command.find(':') - 1);
	if(result->channel.at(0) != '#')
		result->channel = '#' + result->channel;
	command = command.substr(command.find(':') + 1);
	while (command.find(',') != std::string::npos || command.find(':') != std::string::npos)
	{
		if (command.find(',') != std::string::npos)
		{
			tmp = command.substr(0, command.find(','));
			command = command.substr(command.find(',') + 1);
			if (tmp[0] != '#')
				tmp = '#' + tmp;
			if(tmp.find(' ') != std::string::npos)
			{
				tmp = tmp.substr(0, tmp.find(' ') - 1);
			}
			if (command.find(' ') != std::string::npos)
			{
				command = command.substr(command.find(' ') + 1);
			}
			result->channels.push_back(tmp);
		}
		else if(command.find(':') != std::string::npos)
		{
			tmp =  command.substr(0, command.find(':'));
			result->reason = tmp;
			command = command.substr(command.find(':') + 1);
		}
		i++;
	}
	if (command[0] != '\0')
	{
		if (command[0] == ' ')
			command = command.substr(1);
		if (command[0] != '#')
			command = '#' + command;
		if(command.find(' ') != std::string::npos)
		{
			command[command.find(' ')] = '\0';
		}
		result->channels.push_back(command);
	}
	result->nb_chann = result->channels.size();
	return(*result);
}

// void		free_t_part(t_part2 var)
// {
// 	int		i = 0;

// 	free(var.channel);
// 	while(i < var.nb_chann)
// 	{
// 		free(var.channels);
// 		i++;
// 	}
// 	std::cout << "Free is done" << std::endl;
// }