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

    game->texture.EA.img = game->image.east;
    game->texture.NO.img = game->image.north;
    game->texture.SO.img = game->image.south;
    game->texture.WE.img = game->image.west;

    game->texture.EA.pixels = (t_color_p *)mlx_get_data_addr(game->texture.EA.img, &game->texture.EA.bpp, &game->texture.EA.row_size, &game->texture.EA.endian);
    game->texture.NO.pixels = (t_color_p *)mlx_get_data_addr(game->texture.NO.img, &game->texture.NO.bpp, &game->texture.NO.row_size, &game->texture.NO.endian);
    game->texture.SO.pixels = (t_color_p *)mlx_get_data_addr(game->texture.SO.img, &game->texture.SO.bpp, &game->texture.SO.row_size, &game->texture.SO.endian);
    game->texture.WE.pixels = (t_color_p *)mlx_get_data_addr(game->texture.WE.img, &game->texture.WE.bpp, &game->texture.WE.row_size, &game->texture.WE.endian);
    return (OK);
}
