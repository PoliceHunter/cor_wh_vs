/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:27:52 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/06 21:01:48 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t		len;
	unsigned	x;

	if (s == NULL)
		return (0);
	len = 0;
	while (1)
	{
		x = *(unsigned*)s;
		if ((x & 0xFF) == 0)
			return (len);
		if ((x & 0xFF00) == 0)
			return (len + 1);
		if ((x & 0xFF0000) == 0)
			return (len + 2);
		if ((x & 0xFF000000) == 0)
			return (len + 3);
		s += 4;
		len += 4;
	}
}
