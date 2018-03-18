/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 16:12:33 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/12 14:00:43 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	refresh(t_global *g)
{
	mlx_clear_window(g->win.mlx_ptr, g->win.win_ptr);
	mlx_destroy_image(g->win.mlx_ptr, g->pic.ptr);
	init_images(g, g->win.max_len, g->win.max_height);
	g->change ? init_ratios(g) : 0;
	g->change = 0;
	draw_point(g);
	mlx_put_image_to_window(g->win.mlx_ptr,
			g->win.win_ptr, g->pic.ptr, 0, 0);
	ft_bzero(&g->fun, sizeof(g->fun));
}

void	dezoom(t_global *g, int zoom)
{
	g->fun.fun = 0;
	g->ax.rx += (zoom) ? 1 : -1;
	g->ax.ry += (zoom) ? 1 : -1;
	g->ax.alt += zoom ? 1 : -1;
	g->ax.alt = ft_ismax(g->ax.alt, 0);
	refresh(g);
}

int		shortcut(int key, t_global *g)
{
	if (key == 36)
	{
		g->proj = !g->proj;
		g->change = 1;
	}
	if (key == 53)
	{
		mlx_destroy_window(g->win.mlx_ptr, g->win.win_ptr);
		exit(1);
	}
	if (key == 69 || key == 78)
		g->ax.alt += (key == 69) ? 1 : -1;
	if (key == 125 || key == 126)
		g->ax.beg_y += (key == 126 ? g->ax.ry : -g->ax.ry);
	if (key == 123 || key == 124)
		g->ax.beg_x += (key == 123 ? g->ax.rx : -g->ax.rx);
	if (key == 12 || key == 13)
		dezoom(g, (key == 12));
	refresh(g);
	return (0);
}

int		fun(int button, int x, int y, t_global *g)
{
	g->fun.fun = 1;
	mlx_clear_window(g->win.mlx_ptr, g->win.win_ptr);
	button == 4 || button == 5 ? dezoom(g, button == 5) : 0;
	if (button < 2 && (g->fun.x || g->fun.y))
	{
		g->ax.x[1] = x;
		g->ax.y[1] = y;
		draw1(g, g->fun.x, g->fun.y);
	}
	if (button == 1 || (!g->fun.x && !g->fun.y))
	{
		g->fun.x = x;
		g->fun.y = y;
	}
	else
		ft_bzero(&g->fun, sizeof(g->fun));
	mlx_put_image_to_window(g->win.mlx_ptr,
			g->win.win_ptr, g->pic.ptr, 0, 0);
	g->fun.fun = 0;
	return (0);
}
