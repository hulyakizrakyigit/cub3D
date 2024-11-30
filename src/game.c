#include "cub3D.h"

void ft_put_pixel(t_game *game, int x, int y, t_color_p color)
{
    game->mlx.img.pixels[y * SCREEN_WIDTH + x] = color;
}
void draw_background(t_game *game)
{
    // Üst yarıyı mavi, alt yarıyı yeşil çiz
    for (int y = 0; y < SCREEN_HEIGHT / 2; y++) 
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            ft_put_pixel(game, x, y, game->ceiling);
        }
    }
    for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++) 
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            ft_put_pixel(game, x, y, game->floor);
        }
    }
}
int	start_game(void *param)
{
    t_game *game;
    game = (t_game *)param;
    game->floor.red = game->map.texture.F.R;
    game->floor.green = game->map.texture.F.G;
    game->floor.blue = game->map.texture.F.B;
    game->ceiling.red = game->map.texture.C.R;
    game->ceiling.green = game->map.texture.C.G;
    game->ceiling.blue = game->map.texture.C.B;
    game->floor.alpha = 0;
    game->ceiling.alpha = 0;
    printf("Floor Color: %d, %d, %d\n", game->floor.red, game->floor.green, game->floor.blue);
    printf("Ceiling Color: %d, %d, %d\n", game->ceiling.red, game->ceiling.green, game->ceiling.blue);
    // printf("Floor: %d, %d, %d\n", game->map.texture.F.R, game->map.texture.F.G, game->map.texture.F.B);
  
    
    draw_background(game);
    mlx_put_image_to_window(game->mlx.mlx, game->mlx.win_ptr, game->mlx.img.img, 0, 0);
return 0;
}