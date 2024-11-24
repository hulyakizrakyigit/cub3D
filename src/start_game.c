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


	fps = ft_itoa((int)(1 / game->time));
	mlx_string_put(game->mlx, game->win_ptr, HEIGHT, WIDTH, 0x00FF0000, fps); // 0x00FF0000??
	free(fps);
	return (0);
}
