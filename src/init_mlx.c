#include "cub3D.h"


t_err init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (perr(__func__, "mlx init failed!"));
    game->win_ptr = mlx_new_window(game->mlx, 800, 600, "cub3D");
    if (!game->win_ptr)
    {
        free(game->mlx);
        return (perr(__func__, "mlx new window failed!"));
    }
    return (OK);
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