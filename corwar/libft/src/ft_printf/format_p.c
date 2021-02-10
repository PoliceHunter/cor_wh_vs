/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:38:58 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 11:39:42 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*format_p(va_list ap)
{
	char			*tmp;
	char			*res;
	char			*base;
	unsigned long	adr;
	int				i;

	if (!(tmp = va_arg(ap, void *)))
		return (ft_strdup("0x0"));
	adr = (unsigned long)tmp;
	if (!(res = (char *)malloc(sizeof(char) * malloc_count(adr) + 1)))
		return (0);
	res[malloc_count(adr)] = 0;
	base = "0123456789abcdef";
	i = 0;
	while (adr >= 1)
	{
		res[i] = base[(adr % 16)];
		adr = (adr - (adr % 16)) / 16;
		i++;
	}
	ft_strrev(res);
	res = ft_strjoin_free2("0x", res);
	return (res);
}

int		malloc_count(unsigned long adr)
{
	int	count;
	int	r;

	count = 0;
	while (adr >= 1)
	{
		r = adr % 16;
		adr = (adr - r) / 16;
		count++;
	}
	return (count);
}
