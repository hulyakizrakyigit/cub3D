#include "cub3D.h"

bool	strevery(int (*func)(int c),  const char *str)
{
	int	i;

	if (!func || !str)
		return (perr(__func__, "'func' or 'str' cannot be null"), 0);
	i = 0;
	while (str[i])
	{
		if (!func(str[i]))
			return (0);
		i++;
	}
	return (1);
}

bool	is_empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\v' || line[i] == '\f' || line[i] == '\r' || line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}


