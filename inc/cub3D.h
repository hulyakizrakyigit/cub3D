# ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/libft/get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


typedef enum e_err
{
	OK = 0,
	ERR = 1
} t_err;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	char 	*path;
	int 	count;
} t_img;

typedef struct s_color
{
	int R;
	int G;
	int B;
	int count;
	char *rgb_str;
	char **rgb_str_arr;

} t_color;

typedef struct s_texture
{
	t_img NO;
	t_img SO;
	t_img WE;
	t_img EA;
	t_color F;
	t_color C;

} t_texture;

typedef struct s_map
{
	char	**map;
	t_texture texture;

} t_map;

typedef struct s_game
{
	t_map	map;


} t_game;

t_err	perr(const char *func, const char *msg);
t_err 	game_init(t_game *game, char *path);
t_err 	map_path_control(char *path);
t_err 	map_init(t_map *map, char *path);


#endif
