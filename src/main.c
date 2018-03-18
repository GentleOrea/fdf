/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:59:48 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/12 12:28:22 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_args(t_global *g, int ac, char **av)
{
	int i;

	i = 0;
	if (ac < 2 || ac > 4)
		exit_parsing(g, NULL, NULL);
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-color") && ft_str_isdigit(av[i + 1]))
			g->col.base_color = ft_atoi(av[++i]);
		else if (ft_strcmp(av[i], "-color"))
			open_file(g, av[i]);
		else
			exit_parsing(g, "{red}base color isn't valid{reset}\n", NULL);
	}
	if (g->col.base_color < 0)
		exit_parsing(g, "{red}base color isn't valid{reset}\n", NULL);
	if (!g->win.height)
		exit_parsing(g, "{red}Nothing to display {reset}\n", NULL);
}

int		main(int ac, char **av)
{
	t_global *g;

	g = (t_global*)ft_memalloc(sizeof(t_global));
	parse_args(g, ac, av);
	init_global(g);
	draw_point(g);
	mlx_put_image_to_window(g->win.mlx_ptr, g->win.win_ptr, g->pic.ptr, 0, 0);
	mlx_key_hook(g->win.win_ptr, shortcut, g);
	mlx_mouse_hook(g->win.win_ptr, fun, g);
	mlx_loop(g->win.mlx_ptr);
	erase_global(g);
	return (0);
}
