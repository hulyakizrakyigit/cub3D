#include "cub3D.h"

t_err image_up(t_game *game)
{
    int w;
    int h;

    game->image.east = mlx_xpm_file_to_image(game->mlx.mlx, "textures/east.xpm", &w, &h);
    game->image.north = mlx_xpm_file_to_image(game->mlx.mlx, "textures/north.xpm", &w, &h);
    game->image.south = mlx_xpm_file_to_image(game->mlx.mlx, "textures/south.xpm", &w, &h);
    game->image.west = mlx_xpm_file_to_image(game->mlx.mlx, "textures/west.xpm", &w, &h);

    if (!game->image.east || !game->image.north || !game->image.south || !game->image.west)
        return (perr(__func__, "xpm file to image failed(check xpm file path)"));
    return (OK);
}