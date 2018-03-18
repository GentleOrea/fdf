/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:26:31 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/12 13:42:43 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	err_mall(t_global *g, void *str)
{
	if (!str)
		exit_parsing(g, "Erreur de malloc\n", NULL);
}

void	exit_parsing(t_global *g, char *str, char *arg)
{
	if (!str)
		ft_printf("Usage : ./fdf map [-color N]\n");
	else
		arg ? ft_printf(str, arg) : ft_printf(str);
	erase_global(g);
	exit(1);
}

void	erase_global(t_global *g)
{
	ft_memdel((void**)&g->win.win_ptr);
	ft_memdel((void**)&g->win.mlx_ptr);
	ft_memdel((void**)&g->pic.str);
	ft_memdel((void**)&g->pic.ptr);
	ft_free_dblint_tab(g->map, g->win.height);
	ft_memdel((void**)&g);
}
