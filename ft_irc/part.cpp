#include <string>
#include <string.h>
#include <iostream>

typedef struct 		s_part
{
	int				nb_chann;
	char			**channels;
	char			*channel;
	std::string		reason;		
}					t_part;

char		*set_up_buffer(int i)
{
	char	*result;
	int		j;

	j = -1;
	result = (char*)malloc(sizeof(char) * (i + 1));
	while(++j <= i)
		result[j] = '\0';
	return (result);
}

t_part	armonize_names(t_part var)
{
	if (var.nb_chann != 0)
	{
		int		j = 0;
		int		k;
		int		l;
		char	*tmp;
		while (j < var.nb_chann)
		{
			k = 0;
			l = 0;
			if (var.channels[j][0] != '#')
			{
				tmp = set_up_buffer(strlen(var.channels[j]) + 1);
				tmp[0] = '#';
				k++;
			}
			else{
				tmp = set_up_buffer(strlen(var.channels[j]));
			}
			while(var.channels[j][l])
			{
				tmp[k] = var.channels[j][l];
				k++;
				l++;
			}
			free(var.channels[j]);
			var.channels[j] = tmp;
			j++;
		}
	}
	if (var.channel[0] != '#')
		{
			char	*channel = set_up_buffer(strlen(var.channel) + 1);
			int		i = 0;

			channel[0] = '#';
			while(var.channel[i])
			{
				channel[i + 1] = var.channel[i];
				i++;
			}
			free(var.channel);
			var.channel	= channel;
		}
	return (var);
}

t_part		split_part_command(const char *command)
{
	int		start;
	int		i;
	int		j;
	int		k;
	int		index;
	char	*buffer;
	t_part	result;

	i = 0;
	start = 0;
	index = 0;
	result.reason = "";
	while(command[start] && command[start] != ':')
		start++;
	result.channel = set_up_buffer(start);
	while (i < start)
	{
		result.channel[i] = command[i];
		i++;
	}
	if (command[start] == '\0')
	{
		result.nb_chann = 0;
		result = armonize_names(result);
		return (result);
	}
	i = 0;
	start++;
	while (command[start + i])
	{
		if (command[start + i] == ',')
			index++;
		i++;
	}
	result.nb_chann = index + 1;
	result.channels = (char**)malloc(sizeof(char*) * (index + 1));
	result.channels[index] = NULL;
	i = 0;
	index = 0;
	while (command[start + i])
	{
		j = 0;
		k = 0;
		while (command[start + i + j] && command[start + i + j] != ',' && command[start + i + j] != ':')
			j++;
		buffer = set_up_buffer(j);
		while (k < j)
		{
			buffer[k] = command[start + i + k];
			k++;
		}
		if (index < result.nb_chann)
			result.channels[index] = buffer;
		else{
			result.reason = buffer;
		}

		j == 0 ? i++ : i += j;
		if (command[start + i] == ',' || command[start + i] == ':')
			i++;
		index++;
	}
	result = armonize_names(result);
	return (result);
}

void	show_data_parsed_part(t_part var)
{
	int         i;
    int         j = 0;

	i = var.nb_chann;
	std::cout << "chann en cours : " << var.channel << std::endl;
    std::cout << "nb chann a quitter : " << var.nb_chann << std::endl;
	while (j < i)
    {
    	std::cout << "chan " << j << " a quitter : " << var.channels[j] << std::endl;
        j++;
    }
	std::cout << "reason : " << var.reason << std::endl;
}

void		free_t_part(t_part var)
{
	int		i = 0;

	free(var.channel);
	while(i < var.nb_chann)
	{
		free(var.channels[i]);
		i++;
	}
	std::cout << "Free is done" << std::endl;
}