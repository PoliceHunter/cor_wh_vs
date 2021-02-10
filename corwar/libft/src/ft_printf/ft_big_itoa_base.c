/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_big_itoa_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:44:44 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 12:26:38 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*ft_itoa_base_xx(unsigned long int value, unsigned long base)
{
	int					i;
	char				*str;
	unsigned long int	tmp;

	i = 0;
	tmp = value;
	while (tmp >= base)
	{
		tmp = tmp / base;
		i++;
	}
	if (!(str = (char *)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i + 1] = '\0';
	while (i >= 0)
	{
		tmp = value % base;
		str[i] = convert_xx(tmp);
		value /= base;
		i--;
	}
	return (str);
}

char	convert_xx(unsigned long int nb)
{
	if (nb >= 10)
		return ((char)(nb - 10 + 'A'));
	else
		return ((char)(nb + '0'));
}
