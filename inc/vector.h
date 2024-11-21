# ifndef VECTOR_H
# define VECTOR_H

typedef enum e_bool
{
	error = -1,
	my_false,
	my_true
}	t_bool;


typedef struct s_moves
{
	t_bool	esc_key;
	t_bool	right_key;
	t_bool	left_key;
	t_bool	w_key;
	t_bool	a_key;
	t_bool	s_key;
	t_bool	d_key;
}	t_moves;
# endif
