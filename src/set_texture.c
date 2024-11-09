#include "cub3D.h"

t_err	control_texture_dir(t_texture *texture)
{
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

t_err	set_texture(char *line, t_map *map)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		set_texture_dir(line, map);
	}
	if (!ft_strncmp(line, "F ", 2))
	{
		if (!check_texture_color(line, map))
			return (ERR);
		set_texture_color_F(&map->texture);
		map->row++;
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		if (!check_texture_color(line, map))
			return (ERR);
		set_texture_color_C(&map->texture);
		map->row++;
	}

	return (OK);
}
void	set_texture_dir(char *line,  t_map *map)
{
	if (!line)
		return ;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		map->texture.NO.path = ft_strtrim(line + 3, "\t\v\f\r\n ");
		map->texture.NO.count++;
		map->row++;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		map->texture.SO.path = ft_strtrim(line + 3, "\t\v\f\r\n ");
		map->texture.SO.count++;
		map->row++;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		map->texture.WE.path = ft_strtrim(line + 3, "\t\v\f\r\n ");
		map->texture.WE.count++;
		map->row++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		map->texture.EA.path = ft_strtrim(line + 3, "\t\v\f\r\n ");
		map->texture.EA.count++;
		map->row++;
	}
}

void	set_texture_color_F(t_texture *texture)
{
	int i;

	i = 0;
	while (texture->F.rgb_str_arr[i])
	{
		if (i == 0)
			texture->F.R = ft_atoi(texture->F.rgb_str_arr[i]);
		if (i == 1)
			texture->F.G = ft_atoi(texture->F.rgb_str_arr[i]);
		if (i == 2)
			texture->F.B = ft_atoi(texture->F.rgb_str_arr[i]);
		i++;
	}
	texture->F.count++;
}
void	set_texture_color_C(t_texture *texture)
{
	int i;

	i = 0;
	while (texture->C.rgb_str_arr[i])
	{
		if (i == 0)
			texture->C.R = ft_atoi(texture->C.rgb_str_arr[i]);
		if (i == 1)
			texture->C.G = ft_atoi(texture->C.rgb_str_arr[i]);
		if (i == 2)
			texture->C.B = ft_atoi(texture->C.rgb_str_arr[i]);
		i++;
	}
	texture->C.count++;
}
