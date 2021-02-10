/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:00:39 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 12:01:07 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*ft_strsub_free(char *s, int start, unsigned int len)
{
	char	*cpy;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(cpy = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (len)
	{
		cpy[i] = s[start + i];
		len--;
		i++;
	}
	cpy[i] = 0;
	free(s);
	return (cpy);
}
