#include "cub3D.h"
#include <sys/time.h>

int	start_game(void *params)
{
	char *fps;
	t_game *game = (t_game *)params;
	struct timeval curr_time;
	static struct timeval old_time = {0, 0};

	gettimeofday(&curr_time, NULL);
	game->time = (double)(curr_time.tv_sec - old_time.tv_sec) + (double)(curr_time.tv_usec - old_time.tv_usec) / 1000000;
	old_time = curr_time;

	fps = ft_itoa((int)(1 / game->time));
	mlx_string_put(game->mlx, game->win_ptr, HEIGHT, WIDTH, 0x00FF0000, fps); // 0x00FF0000??
	free(fps);
}
