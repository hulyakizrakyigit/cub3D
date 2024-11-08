#include "cub3D.h"

t_err	map_control_centrals_items(t_map *map, char *line, int x)
{
	int y;

	y = 0;
	while (line[y])
	{
		if (line[y] == '1' || line[y] == '0' || line[y] == ' ')
			y++;
		else if (line[y] == 'N')
		{
			map->player.x = x;
			map->player.y = y;
			map->player.direction = 'N';
			map->player_count++;
			y++;
		}
		else if (line[y] == 'S')
		{
			map->player.x = x;
			map->player.y = y;
			map->player.direction = 'S';
			map->player_count++;
			y++;
		}
		else if (line[y] == 'W')
		{
			map->player.x = x;
			map->player.y = y;
			map->player.direction = 'W';
			map->player_count++;
			y++;
		}
		else if (line[y] == 'E')
		{
			map->player.x = x;
			map->player.y = y;
			map->player.direction = 'E';
			map->player_count++;
			y++;
		}
		else
		{
			return (perr(__func__, "Invalid map(undefined item)"));
		}

	}
	return (OK);
}

t_err	map_control_centrals(t_map *map)
{
	int i;
	char *line;
	t_err err;

	i = map->map_start + 1;
	while (i <= map->map_end)
	{
		while (map->map[i])
		{
		line = ft_strtrim(map->map[i], "\n\v\t\r ");
		if (((ft_strlen(line) >= 1)) && line[0] ==  '0' && (line[0] != '1' || line[ft_strlen(line) - 1] != '1'))
		{
			return (free(line), perr(__func__, "Invalid map, surrounded by walls3"));
		}
		if (ft_strlen(line) > 1)
		{
			err = map_control_centrals_items(map, line, i);
			if (err != OK || map->player_count > 1)
				return (free(line), perr(__func__, "Invalid map(undefined item) or player count"));
		}
		i++;
		}
	}
	return (free(line), OK);
}

int	map_width(t_map *map)
{
	int i;
	int max;
	int len;

	i = 0;
	max = 0;
	while (map->map[i])
	{
		len = ft_strlen(map->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

t_err map_H(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	map->map_width = map_width(map);
    map->map_H = malloc(sizeof(char *) * (map->map_len - map->row + 1));
    if (!map->map_H)
        return (perr(__func__, "malloc failed(map_H)"));
	while (i < map->map_len - map->row )
	{
		map->map_H[i] = malloc(sizeof(char) * (map->map_width + 1));
		ft_memset(map->map_H[i], 'H', map->map_width + 1);
		map->map_H[i][map->map_width] = '\0';
		i++;
	}
	map->map_H[i] = NULL;
	while (map->map_H[i])
	{
		printf("i: %d %s\n",i, map->map_H[i]);
		i++;
	}
	i = 0;
	while (i < map->map_len - map->row)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] == ' ' || map->map[i][j] == '\t' || map->map[i][j] == '\v' ||
				map->map[i][j] == '\f' || map->map[i][j] == '\r' || map->map[i][j] == '\n')
				map->map_H[i][j] = 'H';
			else
				map->map_H[i][j] = map->map[i][j];
			j++;
		}
		i++;
	}
	i = 0;
	while (map->map_H[i])
	{
		printf("%s\n", map->map_H[i]);
		i++;
	}
	return (OK);
}

t_err	control_player(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	printf("player x: %d\n", map->player.x);
	printf("player y: %d\n", map->player.y);
	if (map->player.x == 0 || map->player.y == 0)
		return (perr(__func__, "Invalid player position"));
	if (map->map_H[map->player.x][map->player.y - 1] == '1' && map->map_H[map->player.x][map->player.y + 1] == '1'&& map->map_H[map->player.x - 1][map->player.y] == '1' && map->map_H[map->player.x + 1][map->player.y] == '1')
		return (perr(__func__, "Invalid player position, surrounded by walls"));
	return (OK);
}
