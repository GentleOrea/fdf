/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:08:41 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/12 14:00:56 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_color(t_global *g)
{
	int i;

	i = -1;
	while (g->col.base_color > 2 && ++i < 3)
	{
		srand(g->col.base_color * i);
		g->col.col[0] |= (rand() % 0xff) << (i * 8);
		g->col.col[1] |= (rand() % 0xff) << (i * 8);
	}
	if (g->col.base_color == 1)
	{
		g->col.col[0] = 0x00CC00;
		g->col.col[1] = 0xffff66;
	}
	else if (!g->col.base_color)
	{
		g->col.col[0] = 0x00A912BA;
		g->col.col[1] = 0x001260BA;
	}
}

int		get_color(int start, int finish, int ratio)
{
	int		ret;
	t_color	a;
	t_color	b;

	ratio = ratio ? abs(ratio) : 1;
	a.r = (start & 0x000000ff);
	a.g = (start & 0x0000ff00) >> 8;
	a.b = (start & 0x00ff0000) >> 16;
	b.r = (finish & 0x000000ff);
	b.g = (finish & 0x0000ff00) >> 8;
	b.b = (finish & 0x00ff0000) >> 16;
	a.r = a.r + ((b.r - a.r) / ratio);
	a.g = a.g + ((b.g - a.g) / ratio);
	a.b = a.b + ((b.b - a.b) / ratio);
	ret = a.r | a.g << 8 | a.b << 16;
	return (ret);
}

void	draw_images(t_global *g, int x, int y, int dir)
{
	int		end;
	int		start;
	int		ratio;

	if (!g->fun.fun)
	{
		start = g->col.col[0] + g->map[g->ax.y1 +
			!g->ax.ori][g->ax.x1 + g->ax.ori] * -g->ax.alt;
		ratio = (dir == abs(g->ax.x[1] - g->ax.x[0]) / 2) ? g->ax.x[1] - x :
			g->ax.y[1] - y;
		if ((g->map[g->ax.y1 + !g->ax.ori][g->ax.x1 + g->ax.ori]
					- g->map[g->ax.y1][g->ax.x1]))
			end = g->col.col[1];
		else
			end = start;
		g->pic.color = get_color(start, end, dir / (ratio | 1));
	}
	else
		g->pic.color = 0x50ffff;
	if (x > 0 && x < g->win.max_len && y > 0 && y < g->win.max_height)
		g->pic.str[x + (y * g->win.max_len)] = g->pic.color;
}
