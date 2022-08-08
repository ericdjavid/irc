#include <string>

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
		result.channels[index] = buffer;
		j == 0 ? i++ : i += j + 1;
		index++;
	}
	return (result);
}