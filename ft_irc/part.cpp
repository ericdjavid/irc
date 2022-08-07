#include <string>

typedef struct 		s_part
{
	int				nb_chann;
	std::string		*channels;
	std::string		reason;		
}					t_part;

char		*set_up_buffer(int i)
{
	char	*result;
	int		j;

	j = -1;
	result = (char*)malloc(sizeof(char) * (i + 1));
	while(++j < i)
		result[j] = '\0';
	return (result);
}

t_part		split_part_command(char *command)
{
	int		i;
	int		j;
	char	*buffer;
	t_part	result;
	
	i = 0;
	while (command[i])
	{
		j = 0;
		while (command[j] && command[j] != ',')
			j++;
		buffer = set_up_buffer(j);
		
		i++;
	}
}