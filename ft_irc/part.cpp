#include <string>
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