#include "cub3D.h"

int main(int ac, char **av)
{
	t_game *game;
	t_err err;

	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}

	game = malloc(sizeof(t_game));
	if (!game)
	{
		perr(__func__, "malloc failed");
		return (1);
	}
	ft_memset(game, 0, sizeof(t_game));
	err = texture_init(&game->map, av[1]);
	if (err != OK)
	{
		perr(__func__, "texture_init failed");
		return (dispose(game), 1);
	}
	err = prepare_map_init(&game->map, av[1]);
	if (err != OK)
	{
		perr(__func__, "map_init failed");
		return (dispose(game), 1);
	}
	err = map_control(&game->map);
	if (err != OK)
	{
		perr(__func__, "map_control failed");
		return (dispose(game), 1);
	}
	err = map_H(&game->map);
	if (err != OK)
	{
		perr(__func__, "map_control_part failed");
		return (dispose(game), 1);
	}
	err = control_player(&game->map);
	if (err != OK)
	{
		perr(__func__, "control_reachable_player failed");
		return (dispose(game), 1);
	}
	err = map_control_part(&game->map);
	if (err != OK)
	{
		perr(__func__, "map_control_part failed");
		return (dispose(game), 1);
	}
	err = validate_map(game->map.map_H);
	if (err != OK)
	{
		perr(__func__, "validate_map failed");
		return (dispose(game), 1);
	}

	init_mlx_and_game(game);
	mlx_hook(game->win_ptr, 17, 0, close_window, &game); //çarpı işaretinden kapanacak
    mlx_key_hook(game->win_ptr, esc_press, &game); //esc ile kapancak
	mlx_hook(game->win_ptr, KeyPress, (1L << 0), key_press_handler, &game);
	mlx_hook(game->win_ptr, KeyRelease, (1L << 1), key_release_handler, &game);
	if (image_up(game) != OK)
	{
		perr(__func__, "image up failed");
		return (dispose(game), 1);
	}
	mlx_loop_hook(game->mlx, start_game, &game);
	mlx_loop(game->mlx);
	return (dispose(game), 0);
}
