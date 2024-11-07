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

int spaceless_len(char *path, t_map *map)
{
	int fd;
	char *line;
	int len;

	len = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perr(__func__, "open failed"));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_empty_line(line) && ft_strlen(line) > 1)
		{
			if ((size_t)map->map_width < ft_strlen(line))
				map->map_width = ft_strlen(line);
			len++;
		}
		free(line);
	}
	close(fd);
	printf("len: %d\n", len);
	return (len);
}
t_err	prepare_map_init(t_map *map, char *path)
{
	int fd;
	char *line;
	int i;
	int j;
	int spaceless;

	i = 0;
	j = 0;
	if (!map || !path)
		return (perr(__func__, "unexpected error"));
	spaceless = (spaceless_len(path, map) - 6);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perr(__func__, "open failed"));
	map->map = malloc(sizeof(char *) * (map->map_len - spaceless + 1));
	if (!map->map)
		return (perr(__func__, "malloc failed"));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (i >= ((map->row)))
		{
			map->map[j] = malloc(sizeof(char) * (map->map_width + 1));
			if (!map->map[j])
				return (strr_arr_dispose(map->map), perr(__func__, "ft_strdup failed"));
			map->map[j] = ft_strdup(line);
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
			printf("line: %s\n", line);
			printf("line[y]: %c\n", line[y]);
			printf("y: %d\n", y);

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
		if ((line && (ft_strlen(line) > 1)) && (line[0] != '1' || line[ft_strlen(line) - 1] != '1'))
		{
			printf("line: %s\n", line);

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
t_err map_control(t_map *map)
{
	int i;
	char *line;
	t_err err;

	i = 0;
	line = malloc(sizeof(char) * (map->map_width + 1));
	while (is_empty_line(map->map[i]) && ft_strlen(map->map[i]) == 1) // <= || ==
		i++;
	map->map_start = i;
	line = ft_strtrim(map->map[i], "\n\v\t\r ");
	if (!line || !all_chars_are(line))
		return (free(line), perr(__func__, "Invalid map, surrounded by walls1"));
	free(line);
	i  = map->map_len - map->row - 1;
	while (is_empty_line(map->map[i]) && ft_strlen(map->map[i]) == 1) // <= || ==
		i--;
	map->map_end = i;
	line = ft_strtrim(map->map[i], "\n\v\t\r ");
	if (!line || !all_chars_are(line))
		return (free(line), perr(__func__, "Invalid map, surrounded by walls2"));
	free(line);
	err = map_control_centrals(map);
	if (err != OK)
		return (err);
	return (OK);
}
