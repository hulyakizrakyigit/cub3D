#include "cub3D.h"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	t_game *game;
	t_err err;

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
		free(game);
		return (1);
	}
	err = prepare_map_init(&game->map, av[1]);
	if (err != OK)
	{
		perr(__func__, "map_init failed");
		free(game);
		return (1);
	}
	err = map_control(&game->map);
	if (err != OK)
	{
		perr(__func__, "map_control failed");
		free(game);
		return (1);
	}
	err = map_H(&game->map);
	if (err != OK)
	{
		perr(__func__, "map_control_part failed");
		free(game);
		return (1);
	}
	err = control_player(&game->map);
	if (err != OK)
	{
		perr(__func__, "control_reachable_player failed");
		free(game);
		return (1);
	}
	err = map_control_part(&game->map);
	if (err != OK)
	{
		perr(__func__, "map_control_part failed");
		free(game);
		return (1);
	}
	err = validate_map(game->map.map_H);
	if (err != OK)
	{
		perr(__func__, "validate_map failed");
		free(game);
		return (1);
	}

	free(game);
	return (0);

}
