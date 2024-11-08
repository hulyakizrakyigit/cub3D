#include "cub3D.h"
#include "libft.h"
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
t_err game_init(t_game *game, char *path)
{
	t_err err;

	err = map_path_control(path);
	if (err != OK)
		return (perr(__func__, "map_path_control failed"));
	game->map.path = ft_strdup(path);
	if (!game->map.path)
		return (perr(__func__, "ft_strdup failed"));
	err = texture_init(&game->map, path);
	if (err != OK)
		return (perr(__func__, "texture_init failed"));
	return (OK);
}
t_err map_path_control(char *path)
{
	int len;
	int fd;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (perr(__func__, "Invalid file extension"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perr(__func__, "open failed"));
	close(fd);
	return (OK);
}

t_err	prepare_map_init(t_map *map, char *path)
{
	int fd;
	char *line;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!map || !path)
		return (perr(__func__, "unexpected error"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perr(__func__, "open failed"));
	map->map = malloc(sizeof(char *) * (map->map_len - map->row + 1));
	if (!map->map)
		return (perr(__func__, "malloc failed"));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (i >= ((map->row)))
		{
			map->map[j] = ft_strdup(line);
			if (!map->map[j])
				return (strr_arr_dispose(map->map), perr(__func__, "ft_strdup failed"));
			j++;
		}
		i++;
		free(line);
	}
	map->map[j] = NULL;
	return (close(fd), OK);
}

bool is_one_or_space(char c)
{
	return (c == '1' || c == ' ');
}
bool all_chars_are(char *str)
{
	while (*str)
	{
		if (!is_one_or_space(*str))
			return (false);
		str++;
	}
	return (true);
}

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

//çevresi kapalı player

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

t_err	control_reachable_player(t_map *map)
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

void flood_fill(char **map, int x, int y)
{
    if (x < 0 || y < 0 || map[y] == NULL || map[y][x] == '\0')
        return;
    if (map[y][x] == 'H')
        return;
    if (map[y][x] == '1' || map[y][x] == '0' || map[y][x] == 'N')
        map[y][x] = 'K';
    else
        return;

    flood_fill(map, x + 1, y);
    flood_fill(map, x - 1, y);
    flood_fill(map, x, y + 1);
    flood_fill(map, x, y - 1);
}

t_err is_map_valid(char **map)
{
    int i;
	int j;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
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

