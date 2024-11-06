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
	printf("spaceless: %d\n", spaceless);
	printf("map->row: %d\n", map->row);
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

t_err map_control(t_map *map)
{
	int i;
	int j;
	char *line;

	i = 0;
	j = 0;
	int d = 0;
	line = malloc(sizeof(char) * (map->map_width + 1));
	while (map->map[d])
	{
		printf("%d %s\n",d, map->map[d]);
		d++;
	}
	while (is_empty_line(map->map[i]) && ft_strlen(map->map[i]) == 1)
	{
		i++;
		continue;
	}
	while (map->map[i][j])
	{
		printf("baş: %s %zu\n", map->map[i], ft_strlen(map->map[i]));
		line = ft_strtrim(map->map[i], "\n\v\t\r ");
		printf("line: %s %zu\n", line, ft_strlen(line));
		if ((size_t)j < (ft_strlen(line) - 1) && line[j] != '1')
		{
			printf("C::::::%c %d\n", line[j], j);
			return (perr(__func__, "Invalid map, surrounded by walls1"));
		}
		j++;
	}
	i = map->map_len - 1;
	j = 0;
	while (is_empty_line(map->map[i]) && ft_strlen(map->map[i]) == 1)
	{
		i--;
		continue;
	}
	while (map->map[i][j])
	{
		line = ft_strtrim(map->map[i], "\n\v\t\r ");
		if (line[j] != '1')
			return (perr(__func__, "Invalid map, surrounded by walls2"));
		j++;
	}
	return (OK);
}
