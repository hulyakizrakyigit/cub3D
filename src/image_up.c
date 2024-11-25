#include "cub3D.h"

t_err image_up(t_game *game)
{
    game->texture.EA.img = mlx_xpm_file_to_image(game->mlx, "textures/east.xpm", &game->texture.EA.row_size, &game->texture.EA.line_count);
    game->texture.NO.img = mlx_xpm_file_to_image(game->mlx, "textures/north.xpm", &game->texture.NO.row_size, &game->texture.NO.line_count);
    game->texture.SO.img = mlx_xpm_file_to_image(game->mlx, "textures/south.xpm", &game->texture.SO.row_size, &game->texture.SO.line_count);
    game->texture.WE.img = mlx_xpm_file_to_image(game->mlx, "textures/west.xpm", &game->texture.WE.row_size, &game->texture.WE.line_count);

    if (!game->texture.EA.img|| !game->texture.NO.img || !game->texture.SO.img || !game->texture.WE.img)
        return (perr(__func__, "xpm file to image failed(check xpm file path)"));

    game->texture.EA.pixels = (t_color_p *)mlx_get_data_addr(game->texture.EA.img, &game->texture.EA.bpp,
            &game->texture.EA.row_size, &game->texture.EA.byte_order);
    game->texture.EA.bpp /= game->texture.EA.row_size / 8;
    game->texture.NO.pixels = (t_color_p *)mlx_get_data_addr(game->texture.NO.img, &game->texture.NO.bpp,
            &game->texture.NO.row_size, &game->texture.NO.byte_order);
    game->texture.NO.bpp /= game->texture.NO.row_size / 8;
    game->texture.SO.pixels = (t_color_p *)mlx_get_data_addr(game->texture.SO.img, &game->texture.SO.bpp,
            &game->texture.SO.row_size, &game->texture.SO.byte_order);
    game->texture.SO.bpp /= game->texture.SO.row_size / 8;
    game->texture.WE.pixels = (t_color_p *)mlx_get_data_addr(game->texture.WE.img, &game->texture.WE.bpp,
            &game->texture.WE.row_size, &game->texture.WE.byte_order);
    game->texture.WE.bpp /= game->texture.WE.row_size / 8;
    if (!game->texture.EA.pixels || !game->texture.NO.pixels || !game->texture.SO.pixels || !game->texture.WE.pixels)
        return (perr(__func__, "mlx get data addr failed"));
//transform texture and flip texture
    return (OK);
}
//mlx_get_data_addr, bir görüntünün (örneğin bir XPM dosyası) bellekteki piksel verilerine doğrudan erişim sağlar.
//bir dizi (texture->data) olarak düzenlenir ve her pikselin rengi, genellikle ARGB (Alpha, Red, Green, Blue) formatında, bir t_color ya da benzeri bir yapıyla temsil edilir.
//texture->data, her bir pikselin bellek adresini içerir. Böylece görüntünün ham bitlerine erişebilirsiniz.

void background_color_init(t_game *game)
{
        game->texture.F.color.alpha = (game->texture.F.A);
        game->texture.F.color.green = (game->texture.F.G);
        game->texture.F.color.blue = (game->texture.F.B);
        game->texture.F.color.red = (game->texture.F.R);

}
