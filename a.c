
static void	draw_face(struct s_draw_hlpr drw)
{
	int		i;
	float	tex_y;
	float	height;
	t_color	*data;

	height = HEIGHT;
	data = fetch_texture_data(drw.tex, drw.tex_x);
	if (!data)
		return ;
	i = 0;
	setup_texture_rendering(&i, &tex_y, &height, &drw.line_height);
	while (i < drw.line_height)
	{
		if (height > HEIGHT)
			tex_y = calculate_texture_y(drw.tex, height, i + \
			((height - HEIGHT) / 2));
		else
			tex_y = calculate_texture_y(drw.tex, drw.line_height, i);
		if (tex_y >= drw.tex->size_line)
			tex_y = drw.tex->size_line - 1;
		ft_put_pixel(&drw.vars->mlx.image, drw.index,
			i + (HEIGHT - drw.line_height) / 2, data[(int)tex_y]);
		i++;
	}
}
void	setup_texture_rendering(int *i, float *texture_y,
	float *full_height, float *line_height)
{
	*i = 0;
	*texture_y = 0;
	if (*line_height < 0)
	{
		printf("Error\nLine_height is negative: %f\n", *line_height);
		*line_height = 0;
	}
	*full_height = *line_height;
	if (*line_height > HEIGHT)
		*line_height = HEIGHT;
}

static void	draw_wall_piece(t_vars *vars, float line_height,
	int index, t_face face)
{
	float	pos_x;
	float	pos_y;

	pos_x = vars->collisions[index].pos.x;
	pos_y = vars->collisions[index].pos.y;
	if (face == south)
		draw_face((struct s_draw_hlpr){.vars = vars, .tex = &vars->tex_south,
			.line_height = line_height, .index = index,
			.tex_x = pos_x - (int)pos_x});
	if (face == west)
		draw_face((struct s_draw_hlpr){.vars = vars, .tex = &vars->tex_west,
			.line_height = line_height, .index = index,
			.tex_x = pos_y - (int)pos_y});
	if (face == north)
		draw_face((struct s_draw_hlpr){.vars = vars, .tex = &vars->tex_north,
			.line_height = line_height, .index = index,
			.tex_x = pos_x - (int)pos_x});
	if (face == east)
		draw_face((struct s_draw_hlpr){.vars = vars, .tex = &vars->tex_east,
			.line_height = line_height, .index = index,
			.tex_x = pos_y - (int)pos_y});
}
struct s_draw_hlpr
{
	t_vars	*vars;
	t_image	*tex;
	float	line_height;
	float	tex_x;
	int		index;
};


t_color	*fetch_texture_data(t_image *texture, float texture_x)
{
	return (texture->data + \
	((int)linear_interpolation(texture_x, 0, texture->size_line) \
	* texture->size_line));
}

float	linear_interpolation(float value, float min, float max)
{
	return ((value * (max - min)) + min);
}
float	calculate_texture_y(t_image *texture, float height, float position)
{
	if (position < 0 || height <= 0)
	{
		printf("Error\nInvalid values for position or height\n");
		return (0.0f);
	}
	return (linear_interpolation(ft_normalize(position, 0, height), 0,
			texture->size_line));
}
void	ft_put_pixel(t_image *image, int x, int y, t_color color)
{
	image->data[x + (image->size_line * y)] = color;
}
