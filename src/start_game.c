#include "cub3D.h"
#include <sys/time.h>
#include <math.h>

t_vec	normalize_vec(t_vec vec)
{
	float magnitude;

	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (magnitude == 0)
		return ((t_vec){.x = 0, .y = 0});
	return ((t_vec){.x = vec.x / magnitude, .y = vec.y / magnitude});
}

t_vec rotate_vec(t_vec vec, float angle)
{
	t_vec rotated_vec;

	rotated_vec.x = vec.x * cos(angle) - vec.y * sin(angle);
	rotated_vec.y = vec.x * sin(angle) + vec.y * cos(angle);
	return (rotated_vec);
}

t_vec inversion_vec(t_vec vec)
{
	return ((t_vec){.x = -vec.x, .y = -vec.y});
}

void	handle_camera(t_game *game, t_bool rotate)
{
	float rot_angle;

	rot_angle = -atan2(game->player.dir.x, game->player.dir.y);
	game->player.dir = rotate_vec(game->player.dir, rotate * game->player.camera_speed * rot_angle);
}

t_vec add_vec(t_vec vec1, t_vec vec2)
{
	return ((t_vec){.x = vec1.x + vec2.x, .y = vec1.y + vec2.y});
}

t_vec scale_vec(t_vec vec, float scale)
{
	return ((t_vec){.x = vec.x * scale, .y = vec.y * scale});
}

void check_player_collision(t_game *game, t_vec next_position) // player_radius
{
	int x;
	int y;

	x = (int)next_position.x;
	y = (int)next_position.y;
	if (y < 0 || y >= game->map.map_height || x < 0 || x >= game->map.map_width)
		return ;
	if (game->map.map[y][x] == '1')
		return ;
	game->player.pos = next_position;
}


void handle_movement(t_game *game, t_vec move_vec)
{
	t_vec new_pos;

	new_pos = add_vec(game->player.pos, scale_vec(move_vec, game->player.move_speed));
	check_player_collision(game, new_pos);
}


void	handle_player(t_game *game)
{
	t_moves moves;
	t_vec move_vec;
	t_bool rotate;
	float player_angle;

	moves = game->moves;
	move_vec = (t_vec){.x = moves.a + moves.d, .y = moves.w + moves.s}; // hareket vektörünü oluştur
	move_vec = normalize_vec(move_vec); // vektörü normalize et
	player_angle = (-atan2(game->player.dir.x, game->player.dir.y));
	move_vec = rotate_vec(move_vec, player_angle);
	move_vec = inversion_vec(move_vec);
	rotate = moves.left + moves.right;
	handle_camera(game, rotate);
	handle_movement(game, move_vec);
}

float rad_to_deg(float angle)
{
	return (angle * 180 / M_PI);
}

void	init_ray(t_raycast *ray, t_vec origin, t_vec vec, char axis)
{
	if (axis == 'x')
	{
		if (vec.x > 0)
		{
			ray->curr_pos.x = (int)origin.x + 1;
			ray->grid_step = 1;
			ray->map_offset = 0;
		}
		else
		{
			ray->curr_pos.x = (int)origin.x;
			ray->grid_step = -1;
			ray->map_offset = -1;
		}
		ray->ray_unit_step_x = 1.0 / fabs(vec.x);
	}
	else
	{
		if (vec.y > 0)
		{
			ray->curr_pos.y = (int)origin.y + 1;
			ray->grid_step = 1;
			ray->map_offset = 0;
		}
		else
		{
			ray->curr_pos.y = (int)origin.y;
			ray->grid_step = -1;
			ray->map_offset = -1;
		}
		ray->ray_unit_step_y = 1.0 / fabs(vec.y);
	}
}

float	vec_magnitude(t_vec vec1, t_vec vec2)
{
	return (sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2)));
}
// t_vec	cal_vertical_hit(t_game *game, t_vec origin, t_vec vec, float *vertical_distance)
// {
// 	t_raycast ray_v;

// 	if (vec.x == 0) // Bölme hatasını önle
// 		return ((t_vec){.x = -1, .y = -1});

// 	init_ray(&ray_v, origin, vec, 'x');
// 	while (ray_v.curr_pos.x >= 0 && ray_v.curr_pos.x < game->map.map_width)
// 	{
// 		ray_v.curr_pos.y = (vec.y / vec.x) * (ray_v.curr_pos.x - origin.x) + origin.y;
// 		if (ray_v.curr_pos.y < 0 || ray_v.curr_pos.y >= game->map.map_height) // Sınır kontrolü
// 			break;

// 		ray_v.collision.pos = (t_vec){.x = ray_v.curr_pos.x, .y = ray_v.curr_pos.y};
// 		if (game->map.map[(int)ray_v.curr_pos.y][(int)ray_v.curr_pos.x] == '1')
// 		{
// 			*vertical_distance = vec_magnitude(origin, ray_v.collision.pos);
// 			return (ray_v.collision.pos);
// 		}

// 		ray_v.curr_pos.x += ray_v.grid_step;
// 	}
// 	return ((t_vec){.x = -1, .y = -1});
// }

// t_vec	cal_horizontal_hit(t_game *game, t_vec origin, t_vec vec, float *horizontal_distance)
// {
// 	t_raycast ray_h;

// 	if (vec.y == 0) // Bölme hatasını önle
// 		return ((t_vec){.x = -1, .y = -1});

// 	init_ray(&ray_h, origin, vec, 'y');
// 	while (ray_h.curr_pos.y >= 0 && ray_h.curr_pos.y < game->map.map_height)
// 	{
// 		ray_h.curr_pos.x = (vec.x / vec.y) * (ray_h.curr_pos.y - origin.y) + origin.x;
// 		if (ray_h.curr_pos.x < 0 || ray_h.curr_pos.x >= game->map.map_width) // Sınır kontrolü
// 			break;

// 		ray_h.collision.pos = (t_vec){.x = ray_h.curr_pos.x, .y = ray_h.curr_pos.y};
// 		if (game->map.map[(int)ray_h.curr_pos.y][(int)ray_h.curr_pos.x] == '1')
// 		{
// 			*horizontal_distance = vec_magnitude(origin, ray_h.collision.pos);
// 			return (ray_h.collision.pos);
// 		}

// 		ray_h.curr_pos.y += ray_h.grid_step;
// 	}
// 	return ((t_vec){.x = -1, .y = -1});
// }

t_vec	cal_vertical_hit(t_game *game, t_vec origin, t_vec vec, float *vertical_distance)
{
	t_raycast ray_v;
	if (vec.x == 0)
		return ((t_vec){.x = -1, .y = -1}); //0,0 bölme hatası
	init_ray(&ray_v, origin, vec, 'x');
	while (ray_v.curr_pos.x >= 0 && ray_v.curr_pos.x < game->map.map_width)
	{
		ray_v.curr_pos.y = (vec.y / vec.x) * (ray_v.curr_pos.x - origin.x) + origin.y;
		if (ray_v.curr_pos.y < 0 || ray_v.curr_pos.y >= game->map.map_height)
			break ;
		ray_v.collision.pos = (t_vec){.x = ray_v.curr_pos.x, .y = ray_v.curr_pos.y};
		*vertical_distance = vec_magnitude(origin, ray_v.collision.pos);
		if (*vertical_distance >= game->max_view_distance)
			break ;
		if (ray_v.curr_pos.y >= 0 && ray_v.curr_pos.y < game->map.map_height)
		{
			if (game->map.map[(int)ray_v.curr_pos.y][(int)ray_v.curr_pos.x] == '1')
				return (ray_v.collision.pos);
		}
		ray_v.curr_pos.x += ray_v.grid_step;
	}
	return ((t_vec){.x = -1, .y = -1}); //0,0
}

t_vec	cal_horizontal_hit(t_game *game, t_vec origin, t_vec vec, float *horizontal_distance)
{
	t_raycast ray_h;
	init_ray(&ray_h, origin, vec, 'y');
	if (vec.y == 0) // 0'a bölme hatası
		return ((t_vec){.x = -1, .y = -1}); //0,0
	while (ray_h.curr_pos.y >= 0 && ray_h.curr_pos.y < game->map.map_height)
	{
		ray_h.curr_pos.x = (vec.x / vec.y) * (ray_h.curr_pos.y - origin.y) + origin.x;
		ray_h.collision.pos = (t_vec){.x = ray_h.curr_pos.x, .y = ray_h.curr_pos.y};
		*horizontal_distance = vec_magnitude(origin, ray_h.collision.pos);
		if (*horizontal_distance >= game->max_view_distance)
			break ;
		if (ray_h.curr_pos.x >= 0 && ray_h.curr_pos.x < game->map.map_width)
		{
			if (game->map.map[(int)ray_h.curr_pos.y][(int)ray_h.curr_pos.x] == '1')
				return (ray_h.collision.pos);
		}
		ray_h.curr_pos.y += ray_h.grid_step;
	}
	return ((t_vec){.x = -1, .y = -1}); //0,0
}

void raycasting(t_game *game, t_vec origin, t_vec vec, t_collision *collision)
{
	t_vec vertical_hit;
	t_vec horizontal_hit;
	float vertical_distance;
	float horizontal_distance;

	vertical_distance = 0;
	horizontal_distance = 0;
	vertical_hit = cal_vertical_hit(game, origin, vec, &vertical_distance);
	horizontal_hit = cal_horizontal_hit(game, origin, vec, &horizontal_distance);
	if (horizontal_distance < vertical_distance)
	{
		collision->pos = horizontal_hit;
		if (origin.y < horizontal_hit.y)
			collision->side = North;
		else
			collision->side = South;
	}
	else
	{
		collision->pos = vertical_hit;
		if (origin.x < vertical_hit.x)
			collision->side = West;
		else
			collision->side = East;
	}
}

void	handle_ray(t_game *game)
{
	int i;
	float angle_offset;
	t_vec rotated;

	game->ray_count = WIDTH;
	angle_offset = -(WIDTH / 2);
	i = 0;
	while (i < game->ray_count)
	{
		game->ray_angles[i] = rad_to_deg(atan(angle_offset / WIDTH));
		rotated = rotate_vec(game->player.dir, game->ray_angles[i]);
		raycasting(game, game->player.pos, rotated, &game->collisions[i]);
		angle_offset += 1;
		i++;
	}
}

void	ft_put_pixel(t_game *game, int x, int y, t_color_p color)
{
	game->mlx_pixels[(x + y * game->mlx_row_size) * 4 + 0] = color.blue;   // Blue
	game->mlx_pixels[(x + y * game->mlx_row_size) * 4 + 1] = color.green;  // Green
	game->mlx_pixels[(x + y * game->mlx_row_size) * 4 + 2] = color.red;    // Red
	game->mlx_pixels[(x + y * game->mlx_row_size) * 4 + 3] = color.alpha;  // Alpha
}

void	draw_background(t_game *game)
{
	int	i;
	int	j;
	t_color_p c_color;
	t_color_p f_color;

	c_color.alpha = 0;
	c_color.red = (unsigned char)(game->texture.C.R);
	c_color.green = (unsigned char)(game->texture.C.G);
	c_color.blue = (unsigned char)(game->texture.C.B);

	f_color.alpha = 0;
	f_color.red = (unsigned char)(game->texture.F.R);
	f_color.green = (unsigned char)(game->texture.F.G);
	f_color.blue = (unsigned char)(game->texture.F.B);

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i < HEIGHT / 2)
				ft_put_pixel(game, j, i, c_color);
			else
				ft_put_pixel(game, j, i, f_color);
			j++;
		}
		i++;
	}
}
static t_color_p get_texture_color(t_img *texture, float tex_x, float tex_y)
{
	int tex_pos_x;
	int tex_pos_y;

	tex_pos_x = (int)(tex_x * texture->row_size);
	tex_pos_y = (int)(tex_y) * texture->row_size;
	return texture->pixels[tex_pos_y + tex_pos_x];
}

static void draw_wall_column(t_game *game, t_draw_params *params, int start_y, int end_y)
{
	int y;
	float tex_y;
	t_color_p color;

	y = start_y;
	while (y < end_y)
	{
		// Y eksenindeki doku koordinatını hesapla
		tex_y = ((y - start_y) / params->wall_height) * params->texture->line_count;

		// Doku piksel rengini al
		color = get_texture_color(params->texture, params->tex_x, tex_y);

		// Pikselleri ekrana çiz
		game->mlx_pixels[(y * game->mlx_row_size + params->column_index) * 4 + 0] = color.blue;
		game->mlx_pixels[(y * game->mlx_row_size + params->column_index) * 4 + 1] = color.green;
		game->mlx_pixels[(y * game->mlx_row_size + params->column_index) * 4 + 2] = color.red;
		game->mlx_pixels[(y * game->mlx_row_size + params->column_index) * 4 + 3] = color.alpha;
		y++;
	}
}

void	draw_side(t_game *game, int i, float wall_height, float tex_x, t_side side)
{
	t_img *texture;
	int start_y;
	int end_y;
	t_draw_params params;

	if (side == North)
		texture = &game->texture.NO;
	else if (side == South)
		texture = &game->texture.SO;
	else if (side == West)
		texture = &game->texture.WE;
	else
		texture = &game->texture.EA;

	start_y = (HEIGHT - wall_height) / 2;
	if (start_y < 0)
		start_y = 0;
	end_y = (HEIGHT + wall_height) / 2;
	if (end_y >= HEIGHT)
		end_y = HEIGHT;
	params.texture = texture;
	params.wall_height = wall_height;
	params.tex_x = tex_x;
	params.column_index = i;
	draw_wall_column(game, &params, start_y, end_y);
}

void	draw_single_wall(t_game *game, float wall_height, int i, t_side side)
{
	t_vec collision_pos;
	float tex_x;

	collision_pos = game->collisions[i].pos;
	if (side == North)
	{
		tex_x = collision_pos.x - (int)collision_pos.x;
		draw_side(game, i, wall_height, tex_x, North);
	}
	else if (side == South)
	{
		tex_x = collision_pos.x - (int)collision_pos.x;
		draw_side(game, i, wall_height, tex_x, South);
	}
	else if (side == West)
	{
		tex_x = collision_pos.y - (int)collision_pos.y;
		draw_side(game, i, wall_height, tex_x, West);
	}
	else
	{
		tex_x = collision_pos.y - (int)collision_pos.y;
		draw_side(game, i, wall_height, tex_x, East);
	}
}

bool	is_zero_vec(t_vec vec)
{
	return (fabs(vec.x) < 0.001 && fabs(vec.y) < 0.001);
}

float	deg_to_rad(float degree)
{
	return ((degree / 180) * M_PI);
}

void	draw_walls(t_game *game)
{
	int	i;
	float distance;
	float wall_height;
	t_vec collision_pos;

	i = 0;
	while (i < game->ray_count)
	{
		collision_pos = game->collisions[i].pos;
		if (is_zero_vec(collision_pos))
		{
			i++;
			continue ;
		}
		distance = vec_magnitude(game->player.pos, collision_pos);
		if (distance <= 0)
		{
			i++;
			continue ;
		}
		wall_height =  HEIGHT / (distance * cos(deg_to_rad(game->ray_angles[i]))); //duvarın yüksekliği = ekran yüksekliği / (düzeltilmiş mesafe)
		draw_single_wall(game, wall_height, i, game->collisions[i].side);
		i++;
	}
}

int	start_game(void *params)
{
	char *fps;
	t_game *game = (t_game *)params;
	struct timeval curr_time;
	static struct timeval old_time = {0, 0};

	gettimeofday(&curr_time, NULL);
	game->time = (double)(curr_time.tv_sec - old_time.tv_sec) + (double)(curr_time.tv_usec - old_time.tv_usec) / 1000000;
	old_time = curr_time;

	handle_player(game);
	handle_ray(game);

	draw_background(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win_ptr, game->mlx_img, 0, 0);
	fps = ft_itoa((int)(1 / game->time));
	mlx_string_put(game->mlx, game->win_ptr, HEIGHT, WIDTH, 0x00FF0000, fps); // 0x00FF0000??
	free(fps);
	return (0);
}
