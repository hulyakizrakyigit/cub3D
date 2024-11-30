#include "cub3D.h"

int key_press_handler(int key_code, t_game *game)
{
	if (key_code == W_KEY)
		game->moves->w = -1;
	else if (key_code == A_KEY)
		game->moves->a = -1;
	else if (key_code == S_KEY)
		game->moves->s = -1;
	else if (key_code == D_KEY)
		game->moves->d = -1;
	else if (key_code == LEFT_KEY)
		game->moves->left = -1;
	else if (key_code == RIGHT_KEY)
		game->moves->right = -1;

	return (0);

}

int	key_release_handler(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->moves->w = 0;
	else if (keycode == A_KEY)
		game->moves->a = 0;
	else if (keycode == S_KEY)
		game->moves->s = 0;
	else if (keycode == D_KEY)
		game->moves->d = 0;
	else if (keycode == LEFT_KEY)
		game->moves->left = 0;
	else if (keycode == RIGHT_KEY)
		game->moves->right = 0;

	return (0);
}
int close_window(t_game *game)
{
	if (game->mlx_img)
		mlx_destroy_image(game->mlx, game->mlx_img);
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
