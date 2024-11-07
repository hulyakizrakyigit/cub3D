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
bool str_include(char *str, char c)
{
	while (*str)
	{
		if (*str != c)
			return (false);
	}
	return (true);
}


t_err map_control(t_map *map)
{
	int i;
	int j;
	char *line;

	i = 0;
	j = 0;
	line = malloc(sizeof(char) * (map->map_width + 1));
	while (is_empty_line(map->map[i]) && ft_strlen(map->map[i]) == 1) // <= || ==
		i++;
	line = ft_strtrim(map->map[i], "\n\v\t\r ");
	printf("lineaaaaaa: %s\n", line);
	if (!line || !(str_include(line, '1') || str_include(line, '0')))
		return (perr(__func__, "Invalid map, surrounded by walls1"));
	free(line);
	// i  = map->map_len - map->row - 1;
	// printf("%d\n", i);
	// printf("%s\n", map->map[i]);
	// while (is_empty_line(map->map[i]) && ft_strlen(map->map[i]) == 1) // <= || ==
	// 	i--;
	// while (map->map[i])
	// {
	// 	printf("map[%d]: %s\n", i, map->map[i]);
	// 	line = ft_strtrim(map->map[i], "\n\v\t\r ");
	// 	printf("line: %s\n", line);
	// 	if (!line || !all_chars_are("1", line))
	// 		return (free(line), perr(__func__, "Invalid map, surrounded by walls2"));
	// 	i--;
	// }
	//free(line);
	return (OK);
}
