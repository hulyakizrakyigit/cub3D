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
void	init_variables(t_game *game)
{

}

t_err init_mlx_and_game(t_game *game)
{
    init_var(&game)
    init_player(&game);
    game->map.player.move_speed = 0.2; //0.2;
    game->map.player.camera_speed = 3; //3;
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


