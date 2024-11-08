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
