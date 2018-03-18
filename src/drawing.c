/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:24:46 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/12 13:52:39 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_horizon(t_global *g)
{
	g->ax.ori = 1;
	if ((g->ax.x1 + 1) < 0 || (g->ax.x1 + 1) >= g->win.len)
		return ;
	if (g->proj)
	{
		g->ax.x[1] = (((g->ax.x1 + 1) * g->ax.rx) - g->ax.y1 * g->ax.ry) / 2;
		g->ax.y[1] = (g->map[g->ax.y1][g->ax.x1 + 1] * -g->ax.alt)
			+ ((g->ax.x1 + 1) * g->ax.rx) / 4 + (g->ax.y1 * g->ax.ry) / 4;
	}
	else
	{
		g->ax.x[1] = ((g->ax.x1 + 1) * g->ax.rx)
			+ ((g->map[g->ax.y1][g->ax.x1 + 1] * -g->ax.alt) / 2);
		g->ax.y[1] = (g->ax.y1 * g->ax.ry)
			+ ((g->map[g->ax.y1][g->ax.x1 + 1] * -g->ax.alt) / 4);
	}
	g->ax.x[1] = g->ax.x[1] + g->ax.beg_x;
	g->ax.y[1] = g->ax.y[1] + g->ax.beg_y;
	if (g->ax.x[1] > 0 && g->ax.x[1] > 0 && g->ax.y[1] > 0 && g->ax.y[0] > 0)
		draw1(g, g->ax.x[0], g->ax.y[0]);
}

void	draw_vert(t_global *g)
{
	g->ax.ori = 0;
	if ((g->ax.y1 + 1) < 0 || (g->ax.y1 + 1) >= g->win.height)
		return ;
	if (g->proj)
	{
		g->ax.x[1] = (g->ax.x1 * g->ax.rx - ((g->ax.y1 + 1) * g->ax.ry)) / 2;
		g->ax.y[1] = (g->map[g->ax.y1 + 1][g->ax.x1] * -g->ax.alt) +
			(g->ax.x1 * g->ax.rx) / 4 + ((g->ax.y1 + 1) * g->ax.ry) / 4;
	}
	else
	{
		g->ax.x[1] = (g->ax.x1 * g->ax.rx) + ((g->map[g->ax.y1 + 1][g->ax.x1]
					* -g->ax.alt) / 2);
		g->ax.y[1] = ((g->ax.y1 + 1) * g->ax.ry)
			+ ((g->map[g->ax.y1 + 1][g->ax.x1] * -g->ax.alt) / 4);
	}
	g->ax.y[1] = g->ax.y[1] + g->ax.beg_y;
	g->ax.x[1] = g->ax.x[1] + g->ax.beg_x;
	if (g->ax.x[1] > 0 && g->ax.x[1] > 0 && g->ax.y[1] > 0 && g->ax.y[0] > 0)
		draw1(g, g->ax.x[0], g->ax.y[0]);
}

void	draw_point(t_global *g)
{
	g->ax.y1 = -1;
	while (++g->ax.y1 < g->win.height)
	{
		g->ax.x1 = -1;
		while (++g->ax.x1 < g->win.len)
		{
			if (g->proj)
			{
				g->ax.x[0] = (g->ax.x1 * g->ax.rx - g->ax.y1 * g->ax.ry) / 2;
				g->ax.y[0] = (g->map[g->ax.y1][g->ax.x1] * -g->ax.alt) +
					(g->ax.x1 * g->ax.rx) / 4 + (g->ax.y1 * g->ax.ry) / 4;
			}
			else
			{
				g->ax.x[0] = (g->ax.x1 * g->ax.rx)
					+ ((g->map[g->ax.y1][g->ax.x1] * -g->ax.alt) / 2);
				g->ax.y[0] = (g->ax.y1 * g->ax.ry)
					+ ((g->map[g->ax.y1][g->ax.x1] * -g->ax.alt) / 4);
			}
			g->ax.y[0] = g->ax.y[0] + g->ax.beg_y;
			g->ax.x[0] = g->ax.x[0] + g->ax.beg_x;
			draw_horizon(g);
			draw_vert(g);
		}
	}
}

void	decr(int *x1, int *y1, int inc[2], int dir)
{
	if (dir)
		*x1 += inc[AX_X];
	else
		*y1 += inc[AX_Y];
}

void	draw1(t_global *g, int x, int y)
{
	int			e;
	int			d[2];
	int			dir;
	int			inc[2];
	int			i;

	i = -1;
	inc[AX_X] = (g->ax.x[1] - x < 0) ? -1 : 1;
	inc[AX_Y] = (g->ax.y[1] - y < 0) ? -1 : 1;
	d[AX_X] = abs(g->ax.x[1] - x);
	d[AX_Y] = abs(g->ax.y[1] - y);
	e = ft_ismax(d[AX_X], d[AX_Y]) / 2;
	dir = (e == d[AX_X] / 2);
	draw_images(g, g->ax.x[0], g->ax.y[0], d[dir ? AX_X : AX_Y]);
	while (++i <= (d[dir ? AX_X : AX_Y]))
	{
		decr(&x, &y, inc, dir & 1);
		e += d[dir ? AX_Y : AX_X];
		if (e >= d[dir ? AX_X : AX_Y])
		{
			e -= d[dir ? AX_X : AX_Y];
			decr(&x, &y, inc, (!dir) & 1);
		}
		draw_images(g, x, y, d[dir ? AX_X : AX_Y]);
	}
}
