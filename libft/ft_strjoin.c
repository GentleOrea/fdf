/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:17:29 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/04 15:33:58 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		*concat(int i2, char const *s1, char const *s2, char *fresh)
{
	int i;

	i = 0;
	while (s1[i])
	{
		fresh[i] = s1[i];
		i++;
	}
	while (s2[i2])
	{
		fresh[i] = s2[i2];
		i++;
		i2++;
	}
	fresh[i] = '\0';
	ft_memdel((void**)&s2);
	ft_memdel((void**)&s1);
	return (fresh);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		i2;
	char	*fresh;

	fresh = NULL;
	if (!(s1 && s2))
		return (NULL);
	i = ft_strlen(s1);
	i2 = ft_strlen(s2);
	if ((fresh = (char*)malloc((i + i2 + 1) * sizeof(char))) == NULL)
		return (NULL);
	i2 = 0;
	return (concat(i2, s1, s2, fresh));
}
