/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsig_itoa_long.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:01:14 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 12:02:29 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char		*ft_itoa_unsigned_long(unsigned long int n)
{
	char			*s;
	int				len;
	unsigned long	num;

	num = n;
	len = ft_nbrlen_unsigned_long(num);
	if (!(s = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len--] = '\0';
	if (n == 0)
	{
		s[0] = '0';
		return (s);
	}
	while (num != 0)
	{
		if (num > 0)
			s[len--] = '0' + (num % 10);
		num = num / 10;
	}
	return (s);
}

int			ft_nbrlen_unsigned_long(unsigned long int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}
