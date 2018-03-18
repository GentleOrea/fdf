/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:31:40 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/12 11:14:25 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_images(t_global *g, int len, int height)
{
	g->pic.ptr = mlx_new_image(g->win.mlx_ptr, len, height);
	g->pic.str = (int *)mlx_get_data_addr(g->pic.ptr,
			&(g->pic.bpp), &(g->pic.s_l), &(g->pic.endian));
}

void	init_ratios(t_global *g)
{
	g->ax.rx = g->win.max_len / (g->win.len * (g->proj ? 1 : 2));
	g->ax.ry = g->win.max_height / (g->win.height * (g->proj ? 1 : 2));
	g->ax.beg_x = g->win.max_len / (g->proj ? 2 : 4);
	g->ax.beg_y = g->win.max_height / 4;
}

void	init_global(t_global *g)
{
	g->win.max_len = 1000;
	g->win.max_height = 1000;
	g->win.mlx_ptr = mlx_init();
	g->win.win_ptr = mlx_new_window(g->win.mlx_ptr,
			g->win.max_len, g->win.max_height, "fdf");
	init_images(g, g->win.max_len, g->win.max_height);
	g->proj = 1;
	init_ratios(g);
	g->ax.alt = 10;
	init_color(g);
}
