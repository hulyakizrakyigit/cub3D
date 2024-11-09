# ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/libft/get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdbool.h>

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


typedef struct s_player
{
	int x;
	int y;
	char direction;
} t_player;
typedef struct s_map
{
	char	**map;
	char	**map_H;
	t_texture texture;
	char	*path;
	int		row;
	int 	map_len;
	int 	map_width;
	int 	map_start;
	int 	map_end;
	int 	player_count;
	t_player player;
} t_map;

typedef struct s_game
{
	t_map	map;

} t_game;

// err.c
t_err	perr(const char *func, const char *msg);

//init.c
t_err 	game_init(t_game *game, char *path);
t_err 	map_path_control(char *path);
t_err	prepare_map_init(t_map *map, char *path);

//control_map_items.c
t_err	map_control_centrals_items(t_map *map, char *line, int x);
t_err	map_control_centrals(t_map *map);
int	map_width(t_map *map);
t_err map_H(t_map *map);
t_err	control_player(t_map *map);

//control_map.c
t_err is_map_valid(char **map);
t_err validate_map(char **map);
t_err map_control_part(t_map *map);
t_err	map_control(t_map *map);

//helper.c
void flood_fill(char **map, int x, int y);
bool is_one_or_space(char c);
bool all_chars_are(char *str);

//init_texture.c
t_err	texture_init(t_map *map, char *path);
t_err	control_texture_color(t_color *color);
t_err	is_invalid_color(char **rgb_str_arr);
t_err	check_texture_color(char *line,  t_map *map);

//set_texture.c
t_err	control_texture_dir(t_texture *texture);
t_err	set_texture(char *line, t_map *map);
void	set_texture_dir(char *line,  t_map *map);
void	set_texture_color_F(t_texture *texture);
void	set_texture_color_C(t_texture *texture);

//str_utils.c
bool	strevery(int (*func)(int c),  const char *str);
bool	is_empty_line(char *line);

//dispose.c
void	dispose(t_game *game);
void	strr_arr_dispose(char **arr);


#endif
