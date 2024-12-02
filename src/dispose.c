#include "cub3D.h"

void	strr_arr_dispose(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	dispose(t_game *game)
{
	// if (game->map.map)
	// 	strr_arr_dispose(game->map.map);
	// if (game->map.map_H)
	// 	strr_arr_dispose(game->map.map_H);
	// if (game->map.texture.NO.path)
	// 	free(game->map.texture.NO.path);
	// if (game->map.texture.SO.path)
	// 	free(game->map.texture.SO.path);
	// if (game->map.texture.WE.path)
	// 	free(game->map.texture.WE.path);
	// if (game->map.texture.EA.path)
	// 	free(game->map.texture.EA.path);
	// if (game->map.texture.F.rgb_str)
	// 	free(game->map.texture.F.rgb_str);
	// if (game->map.texture.F.rgb_str_arr)
	// 	strr_arr_dispose(game->map.texture.F.rgb_str_arr);
	// if (game->map.texture.C.rgb_str)
	// 	free(game->map.texture.C.rgb_str);
	// if (game->map.texture.C.rgb_str_arr)
	// 	strr_arr_dispose(game->map.texture.C.rgb_str_arr);
	free(game);
}
