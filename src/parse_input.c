/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:28:43 by ygarrot           #+#    #+#             */
/*   Updated: 2018/03/12 13:42:13 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	open_file(t_global *g, char *file)
{
	t_map	*map;
	t_map	*begin;
	int		fd;

	if (g->map)
		exit_parsing(g, "{red}You already gave me a map{reset}\n", NULL);
	if ((fd = open(file, O_RDONLY)) < 0)
		exit_parsing(g, "{red}Couldn't open {yellow}%s{reset}\n", file);
	err_mall(g, map = (t_map*)ft_memalloc(sizeof(t_map)));
	begin = map;
	while (get_next_line(fd, &map->len) > 0)
	{
		err_mall(g, map->next = (t_map*)ft_memalloc(sizeof(t_map)));
		map = map->next;
		++g->win.height;
	}
	err_mall(g, g->map = (int**)ft_memalloc(g->win.height * sizeof(int*)));
	parse_input(g, begin);
	while (begin)
	{
		map = begin;
		begin = map->next;
		ft_memdel((void**)&map->len);
		ft_memdel((void**)&map);
	}
}

void	parse_input(t_global *g, t_map *map)
{
	char	**temp_split;
	int		i2;
	int		i;

	i = -1;
	while (++i < g->win.height)
	{
		i2 = -1;
		temp_split = ft_strsplit(map->len, ' ');
		if (g->win.len != ft_tablen(temp_split) && g->win.len)
			exit_parsing(g, "{red}Error in parsing{reset}\n", NULL);
		else
			g->win.len = ft_tablen(temp_split);
		err_mall(g, g->map[i] = (int*)ft_memalloc(g->win.len * sizeof(int)));
		while (temp_split[++i2])
			g->map[i][i2] = ft_atoi(temp_split[i2]);
		ft_free_dblechar_tab(temp_split);
		map = map->next;
	}
}
