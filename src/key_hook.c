#include "cub3D.h"

int key_press_handler(int key_code, t_game *game)
{
	if (key_code == W_KEY)
		game->moves.w_key = -1;
	else if (key_code == A_KEY)
		game->moves.a_key = -1;
	else if (key_code == S_KEY)
		game->moves.s_key = -1;
	else if (key_code == D_KEY)
		game->moves.d_key = -1;
	else if (key_code == LEFT_KEY)
		game->moves.left_key = -1;
	else if (key_code == RIGHT_KEY)
		game->moves.right_key = -1;
	return (0);
}

int	key_release_handler(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->moves.w_key = 0;
	else if (keycode == A_KEY)
		game->moves.a_key = 0;
	else if (keycode == S_KEY)
		game->moves.s_key = 0;
	else if (keycode == D_KEY)
		game->moves.d_key = 0;
	else if (keycode == LEFT_KEY)
		game->moves.left_key = 0;
	else if (keycode == RIGHT_KEY)
		game->moves.right_key = 0;

	return (0);
}
int close_window(t_game *game)
{
    if (game->win_ptr)
        mlx_destroy_window(game->mlx, game->win_ptr);
    free(game);
    exit(0);
}

int esc_press(int keycode, t_game *game)
{
    if (keycode == 53)
        close_window(game);
    return (0);
}
