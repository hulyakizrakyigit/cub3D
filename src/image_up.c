#include "cub3D.h"

t_err image_up(t_game *game)
{
    game->east.img = mlx_xpm_file_to_image(game->mlx, "textures/east.xpm", game->east.size_line, game->east.line_count);
    game->north.img = mlx_xpm_file_to_image(game->mlx, "textures/north.xpm", game->north.size_line, game->north.line_count);
    game->south.img = mlx_xpm_file_to_image(game->mlx, "textures/south.xpm", game->south.size_line, game->south.line_count);
    game->west.img = mlx_xpm_file_to_image(game->mlx, "textures/west.xpm", game->west.size_line, game->west.line_count);

    if (!game->east.img || !game->north.img || !game->south.img || !game->west.img)
        return (perr(__func__, "xpm file to image failed(check xpm file path)"));

    game->east.data = (t_color *)mlx_get_data_addr(game->east.img, &game->east.bits_per_pixel,
            &game->east.size_line, &game->east.endian);
    game->east.bits_per_pixel /= game->east.size_line / 8;
    game->north.data = (t_color *)mlx_get_data_addr(game->north.img, &game->north.bits_per_pixel,
            &game->north.size_line, &game->north.endian);
    game->north.bits_per_pixel /= game->north.size_line / 8;
    game->south.data = (t_color *)mlx_get_data_addr(game->south.img, &game->south.bits_per_pixel,
            &game->south.size_line, &game->south.endian);
    game->south.bits_per_pixel /= game->south.size_line / 8;
    game->west.data = (t_color *)mlx_get_data_addr(game->west.img, &game->west.bits_per_pixel,
            &game->west.size_line, &game->west.endian);
    game->west.bits_per_pixel /= game->west.size_line / 8;
    if (!game->east.data || !game->north.data || !game->south.data || !game->west.data)
        return (perr(__func__, "mlx get data addr failed"));
//transform texture and flip texture
    return (OK);
}
//mlx_get_data_addr, bir görüntünün (örneğin bir XPM dosyası) bellekteki piksel verilerine doğrudan erişim sağlar.
//bir dizi (texture->data) olarak düzenlenir ve her pikselin rengi, genellikle ARGB (Alpha, Red, Green, Blue) formatında, bir t_color ya da benzeri bir yapıyla temsil edilir.
//texture->data, her bir pikselin bellek adresini içerir. Böylece görüntünün ham bitlerine erişebilirsiniz.
void    init_win(t_game *game)
{
    game->win_height = HEIGHT;
    game->win_width = WIDTH;
    
}
