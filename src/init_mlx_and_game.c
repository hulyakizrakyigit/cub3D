#include "cub3D.h"

void init_player(t_game *game)
{
    if (game->map.player.direction == 'N')
        game->map.player.dir = (t_vec){.x = 0.0, .y = -1.0};
    else if (game->map.player.direction == 'S')
        game->map.player.dir = (t_vec){.x = 0.0, .y = 1.0};
    else if (game->map.player.direction == 'W')
        game->map.player.dir = (t_vec){.x = -1.0, .y = 0.0};
    else if (game->map.player.direction == 'E')
        game->map.player.dir = (t_vec){.x = 1.0, .y = 0.0};
    game->map.player.pos = (t_vec){.x = game->map.player.x + 0.5, .y = game->map.player.y + 0.5};
}

void	init_var(t_game *game)
{
    game->moves = (t_moves *)malloc(sizeof(t_moves));
    game->moves->a = 0;
    game->moves->s = 0;
    game->moves->d = 0;
    game->moves->w = 0;
    game->moves->left = 0;
    game->moves->right = 0;
    game->moves->esc = 0;
    game->player.pos.x = 4.5;
    game->player.pos.y = 5.5;
    game->player.dir.x = 0.0;
    game->player.dir.y = 1.0;
    game->texture.EA = (t_img){0};
    game->texture.NO = (t_img){0};
    game->texture.SO = (t_img){0};
    game->texture.WE = (t_img){0};
    game->texture.F = (t_color){0};
    game->texture.C = (t_color){0};
    game->map.player_count = 0;
}
void    init_win(t_game *game)
{

    game->win_height = HEIGHT;
    game->win_width = WIDTH;
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("mlx init failed!\n");
        exit(1);
    }
        // return (perr(__func__, "mlx init failed!"));
    //dispose and exit?
    game->win_ptr = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
    if (!game->win_ptr)
    {
        free(game->mlx);
        //dispose and exit?
        // return (perr(__func__, "mlx new window failed!"));
        printf("mlx new window failed!\n");
        exit(1);
    }
    game->mlx_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->mlx_pixels = mlx_get_data_addr(game->mlx_img, &game->mlx_byte_order, &game->mlx_row_size, &game->mlx_line_count);
    if (!game->mlx_img || !game->mlx_pixels)
    {
        mlx_destroy_window(game->mlx, game->win_ptr);
        free(game->mlx);
        //dispose and exit?
        // return (perr(__func__, "mlx new image failed!"));
        printf("mlx new image failed!\n");
        exit(1);
    }
    game->mlx_row_size /= 4;// 4 - 8?
}

void init_mlx_and_game(t_game *game)
{
    init_player(game);
    game->map.player.move_speed = 0.2; //0.2;
    game->map.player.camera_speed = 3; //3;
    init_win(game);
    mlx_put_image_to_window(game->mlx, game->win_ptr, game->mlx_img, 0, 0);
	mlx_do_key_autorepeatoff(game->mlx);
}


