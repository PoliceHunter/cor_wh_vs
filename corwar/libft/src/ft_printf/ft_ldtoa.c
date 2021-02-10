/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:51:13 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/23 19:20:08 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*ft_ldtoa(long double num, unsigned int precision)
{
	char	*res;
	char	*rest;

	if (num == 0)
		return (ft_strdup("0"));
	if (precision == 0)
		precision = 6;
	res = ldtoa_integer_part(num);
	if ((rest = ldtoa_rest_part(num > 0 ? num : -num, precision)))
	{
		res = ft_strjoin_free(res, rest);
		free(rest);
	}
	return (res);
}
