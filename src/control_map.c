#include "cub3D.h"

t_err is_map_valid(char **map)
{
    int i;
	int j;

	i = 0;
    while (map[i])
    {
	j = 0;
		while (map[i][j])
		{
		if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == 'N')
			return (perr(__func__, "invalid map, map count is not one"));
		j++;
		}
	i++;
    }
    return (OK);
}

t_err validate_map(char **map)
{
    int start_x;
	int start_y;
	int i;
	int j;
	t_err err;

	start_x = -1;
	start_y = -1;
	i = 0;

	while (map[i] != NULL && start_x == -1)
    {
	j = 0;
	while (map[i][j] != '\0')
	{
	if (map[i][j] == '1')
	{
		start_y = i;
		start_x = j;
			break;
	}
	j++;
	}
	i++;
}
    if (start_x != -1 && start_y != -1)
        flood_fill(map, start_x, start_y);
	err = is_map_valid(map);
	if (err != OK)
		return (perr(__func__, "is_map_valid failed"));
    return (OK);
}

t_err map_control_part(t_map *map)
{
	int	i;
	int	j;
	char p;

	i = 0;
	p = map->player.direction;
	while (map->map_H[i])
	{
		j = 0;
		while (map->map_H[i][j])
		{
			if (map->map_H[i][j] == 'H')
			{
				if ((map->map_H[i][j + 1] && (map->map_H[i][j + 1] == '0' || map->map_H[i][j + 1] == p)) ||
				(j != 0 && map->map_H[i][j - 1] && (map->map_H[i][j - 1] == '0' || map->map_H[i][j - 1] == p)) ||
				(map->map_H[i + 1] && (map->map_H[i + 1][j] == '0' || map->map_H[i + 1][j] == p)) ||
				(i != 0 && map->map_H[i - 1] && (map->map_H[i - 1][j] == '0' || map->map_H[i - 1][j] == p)))
					return (perr(__func__, "Invalid map, surrounded by walls(space and 0)"));
			}
		j++;
		}
	i++;
	}
	return (OK);
}

t_err	map_control(t_map *map)
{
	int i;
	char *line;
	t_err err;

	i = 0;
	line = malloc(sizeof(char) * (map->map_width + 1));
	if (!line)
		return (perr(__func__, "Memory allocation failed"));
	while (is_empty_line(map->map[i]) && ft_strlen(map->map[i]) == 1 && i < map->map_len)
		i++;
	map->map_start = i;
	line = ft_strtrim(map->map[map->map_start], "\n\v\t\r ");
	if (!line || !all_chars_are(line))
		return (free(line), perr(__func__, "Invalid map, surrounded by walls1"));
	free(line);
	i = map->map_len - map->row - 1;
	while (i >= 0 && map->map[i] && is_empty_line(map->map[i]) && ft_strlen(map->map[i]) == 1)
		i--;
	map->map_end = i;
	line = ft_strtrim(map->map[map->map_end], "\n\v\t\r ");
	if (!line || !all_chars_are(line))
		return (free(line), perr(__func__, "Invalid map, surrounded by walls2"));
	free(line);
	err = map_control_centrals(map);
	if (err != OK)
		return (perr(__func__, "map_control_centrals failed"));
	return (OK);
}
