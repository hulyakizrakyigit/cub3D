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

	free(game);
	return (0);

}
