/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func_for_f.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jczech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:16:22 by jczech            #+#    #+#             */
/*   Updated: 2020/02/23 19:26:16 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

long double		ft_pow(long double num, unsigned long power)
{
	long double	tmp;

	tmp = num;
	if (power == 0)
		return (1.);
	while (--power != 0)
		num *= tmp;
	return (num);
}

long double		get_rest(long double num)
{
	int			dec_count;
	long double	tmp;

	dec_count = get_integer_part_decimal_count(num);
	if (dec_count == 0)
		return (num);
	tmp = ft_pow(10., dec_count - 1);
	while (dec_count-- != 0)
	{
		num -= (short)(num / tmp) * tmp;
		tmp /= 10;
	}
	return (num);
}

long double		get_int(long double num)
{
	return (num - get_rest(num));
}

int				is_only_int(long double num)
{
	return ((num / ft_pow(10., get_integer_part_decimal_count(num))) == 0);
}
