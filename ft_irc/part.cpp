#include <string>

typedef struct 		s_part
{
	int				nb_chann;
	char			**channels;
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
	int		i;
	int		j;
	int		k;
	int		index;
	char	*buffer;
	t_part	result;

	i = 0;
	index = 0;
	result.reason = "";
	while (command[i])
	{
		if (command[i] == ',' || command[i] == ':')
			index++;
		i++;
	}
	result.nb_chann = index;
	result.channels = (char**)malloc(sizeof(char*) * (index + 1));
	result.channels[index] = NULL;
	i = 0;
	index = 0;
	while (command[i])
	{
		j = 0;
		k = 0;
		while (command[i + j] && command[i + j] != ',' && command[i + j] != ':')
			j++;
		buffer = set_up_buffer(j);
		while (k < j)
		{
			buffer[k] = command[i + k];
			k++;
		}
		result.channels[index] = buffer;
		j == 0 ? i++ : i += j;
		index++;
	}
	return (result);
}