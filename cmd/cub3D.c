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
	game = &(t_game){0};
	err = game_init(game, av[1]);
	if (err != OK)
	{
		perr(__func__, "game_init failed");
		free(game);
		return (1);
	}
	free(game);
	return (0);

}
