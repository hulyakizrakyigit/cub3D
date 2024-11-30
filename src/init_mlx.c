#include "cub3D.h"


t_err init_mlx(t_game *game)
{
    game->mlx.mlx = mlx_init();
    if (!game->mlx.mlx)
        return (perr(__func__, "mlx init failed!"));
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx, 800, 600, "cub3D");
    if (!game->mlx.win_ptr)
    {
        free(game->mlx.mlx);
        return (perr(__func__, "mlx new window failed!"));
    }
    game->mlx.img.img = mlx_new_image(game->mlx.mlx, 800, 600);
    if (!game->mlx.img.img)
    {
        free(game->mlx.mlx);
        free(game->mlx.win_ptr);
        return (perr(__func__, "mlx new image failed!"));
    }
    game->mlx.img.pixels =(t_color_p *) mlx_get_data_addr(game->mlx.img.img, &game->mlx.img.bpp, &game->mlx.img.row_size, &game->mlx.img.endian);
    return (OK);
}

int close_window(t_game *game)
{
    if (game->mlx.win_ptr)
        mlx_destroy_window(game->mlx.mlx, game->mlx.win_ptr);
    free(game);
    exit(0);
}

int esc_press(int keycode, t_game *game)
{
    if (keycode == 53)
        close_window(game);
    return (0);
}