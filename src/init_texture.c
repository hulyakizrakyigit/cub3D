#include "cub3D.h"
#include <fcntl.h>

t_err	texture_init(t_map *map, char *path)
{
	int fd;
	char *line;
	t_err err;

	if (!map || !path)
		return (perr(__func__, "unexpected error"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perr(__func__, "open failed"));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_empty_line(line) && (ft_strlen(line) == 1) && !(map->texture.NO.count == 1 && map->texture.SO.count == 1 && map->texture.WE.count == 1 && map->texture.EA.count == 1 && map->texture.F.count == 1 && map->texture.C.count == 1))
		{
			map->map_len++;
			map->row++;
			free(line);
			continue ;
		}
		err = set_texture(line, map);
		if (err != OK)
			return (free(line), close(fd), err);
		free(line);
		map->map_len++;
	}
	control_texture_dir(&map->texture);
	control_texture_color(&map->texture.C);
	control_texture_color(&map->texture.F);
	return (close(fd), OK);
	}

t_err	control_texture_color(t_color *color)
{
	if (color->R < 0 || color->R > 255)
		return (perr(__func__, "Invalid color R"));
	if (color->G < 0 || color->G > 255)
		return (perr(__func__, "Invalid color G"));
	if (color->B < 0 || color->B > 255)
		return (perr(__func__, "Invalid color B"));
	if (color->count != 1)
		return (perr(__func__, "Invalid color count."));
	return (OK);
}

t_err	is_invalid_color(char **rgb_str_arr)
{
	int i;

	i = 0;
	while (rgb_str_arr[i])
	{
		rgb_str_arr[i] = ft_strtrim(rgb_str_arr[i], "\t\v\f\r\n ");
		if (!strevery(&ft_isdigit, rgb_str_arr[i]) || (rgb_str_arr[i][0] == '\0' && ft_strlen(rgb_str_arr[i]) == 0))
			return (perr(__func__, "Invalid color, not digit"));
		i++;
	}
	if (i != 3)
		return (perr(__func__, "Invalid rgb count, must be 3"));
	return (OK);
}


t_err	check_texture_color(char *line,  t_map *map)
{
	if (!line)
		return (ERR);
	if (!ft_strncmp(line, "F ", 2))
	{
		map->texture.F.rgb_str = ft_strtrim(line + 2, " ");
		map->texture.F.rgb_str_arr = ft_split(map->texture.F.rgb_str, ',');
		if (!is_invalid_color(map->texture.F.rgb_str_arr))
			return (ERR);
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		map->texture.C.rgb_str = ft_strtrim(line + 2, " ");
		map->texture.C.rgb_str_arr = ft_split(map->texture.C.rgb_str, ',');
		if (!is_invalid_color(map->texture.C.rgb_str_arr))
			return (ERR);
	}
	return (OK);
}
