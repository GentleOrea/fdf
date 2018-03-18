/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 16:45:18 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/12 13:51:59 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/includes/libft.h"
# include "mlx.h"
# include <math.h>

# define AX_X 0
# define AX_Y 1

typedef struct	s_coord
{
	int		x[2];
	int		y[2];
	int		x1;
	int		y1;
	int		mid_x;
	int		mid_y;
	int		rx;
	int		ry;
	int		alt;
	int		beg_x;
	int		beg_y;
	int		ori;
}				t_coord;

typedef struct	s_picture
{
	int		*str;
	void	*ptr;
	int		bpp;
	int		endian;
	int		s_l;
	int		color;
}				t_picture;

typedef struct	s_color
{
	int		base_color;
	int		r;
	int		g;
	int		b;
	int		col[2];
}				t_color;

typedef struct	s_window
{
	int			len;
	int			height;
	int			max_len;
	int			max_height;
	int			dir;
	void		*mlx_ptr;
	void		*win_ptr;
	t_coord		c;
}				t_window;

typedef struct	s_map
{
	char			*len;
	struct s_map	*next;
}				t_map;

typedef struct	s_fun
{
	int		x;
	int		y;
	int		fo_x;
	int		fo_y;
	int		fun;
}				t_fun;

typedef struct	s_global
{
	int				**map;
	int				proj;
	int				change;
	t_color			col;
	t_picture		pic;
	t_coord			ax;
	t_window		win;
	t_fun			fun;
}				t_global;

int				shortcut(int key, t_global *global);
int				fun(int button, int x, int y, t_global *g);
int				get_color(int start, int finish, int ratio);
void			refresh(t_global *g);
void			dezoom(t_global *g, int zoom);
void			parse_args(t_global *g, int ac, char **av);
void			init_ratios(t_global *g);
void			erase_global(t_global *g);
void			exit_parsing(t_global *g, char *str, char *arg);
void			draw1(t_global *g, int x, int y);
void			draw_point(t_global *g);
void			err_mall(t_global *g, void *arg);
void			open_file(t_global *g, char *file);
void			parse_input(t_global *g, t_map *temp);
void			init_global(t_global *g);
void			draw_images(t_global *g, int x, int y, int dir);
void			init_images(t_global *g, int len, int height);
void			init_color(t_global *g);
void			decr(int *x1, int *y1, int inc[2], int dir);
void			draw_horizon(t_global *g);
void			draw_vert(t_global *g);
#endif
