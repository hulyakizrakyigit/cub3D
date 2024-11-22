# ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/libft/get_next_line/get_next_line.h"
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdbool.h>


#  define ESC_KEY 53
#  define X_KEY 7
#  define Z_KEY 6
#  define O_KEY 31
#  define Q_KEY 12
#  define W_KEY 13
#  define E_KEY 14
#  define R_KEY 15
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define F_KEY 3
#  define P_KEY 35
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define UP_KEY 126
#  define DOWN_KEY 125

# define HEIGHT			1024
# define WIDTH			1280

typedef enum e_err
{
	OK = 0,
	ERR = 1
} t_err;

typedef enum e_bool
{
	error = -1,
	my_false,
	my_true
}	t_bool;

typedef union u_color_p
{
	struct
	{
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
		unsigned char	alpha;
	};
	unsigned int	value;
}	t_color_p;
typedef struct s_moves
{
	t_bool	esc;
	t_bool	w;
	t_bool	a;
	t_bool	s;
	t_bool	d;
	t_bool	right;
	t_bool	left;
}	t_moves;

typedef enum e_mlx_event
{
	KeyPress = 2,
	KeyRelease = 3
}	t_mlx_event;


typedef struct s_img
{
	void	*img;
	char 	*path;
	int		bpp;
	int		row_size;
	int		line_count;
	int		byte_order;
	int		count;
	t_color_p	*pixels;
}	t_img;

typedef struct s_color
{
	int R;
	int G;
	int B;
	int A;
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


typedef union u_vec2
{
	struct
	{
		float	x;
		float	y;
	};
	float	data[2];
}	t_vec;

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
	float	move_speed;
	float	camera_speed;
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_player;

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
	void	*win_ptr;
	void	*mlx;
	void 	*mlx_img;
	void	*mlx_pixels;
	int		win_height;
	int		win_width;
	int		mlx_row_size;
	int		mlx_line_count;
	int		mlx_byte_order;
	int		time;
	t_player player;
	t_texture texture;
	t_moves moves;

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

//
void init_mlx_and_game(t_game *game);
void	init_var(t_game *game);
void    init_win(t_game *game);
void init_player(t_game *game);



//
t_err image_up(t_game *game);

//key_hook.c
int key_press_handler(int key_code, t_game *game);
int key_release_handler(int keycode, t_game *game);
int close_window(t_game *game);
int esc_press(int keycode, t_game *game);


#endif
