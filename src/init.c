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
	err = map_init(&game->map, path);
	if (err != OK)
		return (perr(__func__, "map_init failed"));
	return (OK);
}
t_err map_path_control(char *path)
{
	int len;
	int fd;

	len = ft_strlen(path);
	printf("%s\n", path);
	printf("%d\n", len);
	printf("%s\n", path + len - 4);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (perr(__func__, "Invalid file extension"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perr(__func__, "open failed"));
	close(fd);
	return (OK);
}

void set_texture_dir(char *line,  t_map *map)
{
	if (!line)
		return ;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		map->texture.NO.path = ft_strtrim(line + 3, " ");
		map->texture.NO.count++;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		map->texture.SO.path = ft_strtrim(line + 3, " ");
		map->texture.SO.count++;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		map->texture.WE.path = ft_strtrim(line + 3, " ");
		map->texture.WE.count++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		map->texture.EA.path = ft_strtrim(line + 3, " ");
		map->texture.EA.count++;
	}
}

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
t_err is_invalid_color(char **rgb_str_arr)
{
	int i;
	int j;

	i = 0;

	while (rgb_str_arr[i])
	{
	ft_strtrim(rgb_str_arr[i], " ");
	printf("%s\n", rgb_str_arr[i]);
		j = 0;
		while (rgb_str_arr[i])
		{
			if (strevery(&ft_isdigit, rgb_str_arr[i]) == 0)
				return (perr(__func__, "Invalid color"));
		}
		i++;
	}
	return (OK);
}


t_err check_texture_color(char *line,  t_map *map)
{
	if (!line)
		return (ERR);
	if (!ft_strncmp(line, "F ", 2))
	{
		printf("AAAAAAAAAAAAAAAAA\n");
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
void set_texture_color_F(t_texture *texture)
{
	int i;
	int j;

	i = 0;
	while (texture->F.rgb_str_arr[i])
	{
		j = 0;
		while (texture->F.rgb_str_arr[i][j])
		{
			if (j == 0)
				texture->F.R = ft_atoi(texture->F.rgb_str_arr[i]);
			else if (j == 1)
				texture->F.G = ft_atoi(texture->F.rgb_str_arr[i]);
			else if (j == 2)
				texture->F.B = ft_atoi(texture->F.rgb_str_arr[i]);
			j++;
		}
		i++;
	}
	texture->F.count++;
	printf("%dFFFFFFFFF\n", texture->F.count);
}
void set_texture_color_C(t_texture *texture)
{
	int i;
	int j;

	i = 0;
	while (texture->C.rgb_str_arr[i])
	{
		j = 0;
		while (texture->C.rgb_str_arr[i][j])
		{
			if (j == 0)
				texture->C.R = ft_atoi(texture->C.rgb_str_arr[i]);
			else if (j == 1)
				texture->C.G = ft_atoi(texture->C.rgb_str_arr[i]);
			else if (j == 2)
				texture->C.B = ft_atoi(texture->C.rgb_str_arr[i]);
			j++;
		}
		i++;
	}
	texture->C.count++;
	printf("%dCCCCCCC\n", texture->C.count);

}

t_err control_texture_color(t_color *color)
{
	printf("%d\n", color->R);
	printf("%d\n", color->G);
	printf("%d\n", color->B);
	if (color->R < 0 || color->R > 255)
		return (perr(__func__, "Invalid color R"));
	if (color->G < 0 || color->G > 255)
		return (perr(__func__, "Invalid color G"));
	if (color->B < 0 || color->B > 255)
		return (perr(__func__, "Invalid color B"));
	printf("%d\n", color->count);
	if (color->count != 1)
		return (perr(__func__, "Invalid color count."));
	return (OK);
}

t_err control_texture_dir(t_texture *texture)
{
	printf("NO: %d\n", texture->NO.count);
	printf("SO: %d\n", texture->SO.count);
	printf("WE: %d\n", texture->WE.count);
	printf("EA: %d\n", texture->EA.count);
	if (texture->NO.count != 1)
	{
	return (perr(__func__, "Invalid texture NO count."));
	}
	if (texture->SO.count != 1)
		return (perr(__func__, "Invalid texture SO count."));
	if (texture->WE.count != 1)
		return (perr(__func__, "Invalid texture WE count."));
	if (texture->EA.count != 1)
		return (perr(__func__, "Invalid texture EAcount."));
	return (OK);
}

t_err set_texture(char *line, t_map *map)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		set_texture_dir(line, map);
	}
	if (!ft_strncmp(line, "F ", 2))
	{
		if (!check_texture_color(line, map))
		{

		printf("ZZZZZZZZZZZZZZZZZ\n");
			return (ERR);
		}
		set_texture_color_F(&map->texture);
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		if (!check_texture_color(line, map))
			return (ERR);
		set_texture_color_C(&map->texture);
	}
	return (OK);
}

t_err map_init(t_map *map, char *path)
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
		err = set_texture(line, map);
		if (err != OK)
		{
			printf("Aaaaaaaaaaaaa");
			return (free(line), close(fd), err);
		}
		free(line);
	}
	control_texture_dir(&map->texture);
	control_texture_color(&map->texture.C);
	control_texture_color(&map->texture.F);
	return (close(fd), OK);
	}
