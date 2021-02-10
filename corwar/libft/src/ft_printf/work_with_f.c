/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jczech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 17:43:10 by jczech            #+#    #+#             */
/*   Updated: 2020/02/23 19:33:26 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static char	*get_str_int_part(long double num, unsigned int dec_count,
		int is_negative)
{
	char	*res;
	char	*ptr;
	char	*tmp;

	res = ft_strnew(dec_count + 1 + (is_negative ? 1 : 0));
	ptr = res;
	ft_fill_by_symbol(res, dec_count, '0');
	if (is_negative)
	{
		*ptr++ = '-';
		num *= -1;
	}
	num /= ft_pow(10, dec_count);
	while (dec_count-- != 0)
	{
		num *= 10;
		tmp = ft_itoa((int)num);
		num -= (int)num;
		ft_strcpy(ptr++, tmp);
		free(tmp);
	}
	return (res);
}

char		*ldtoa_integer_part(long double num)
{
	int				is_negative;
	unsigned int	dec_count;

	is_negative = num < 0;
	dec_count = get_integer_part_decimal_count(num);
	if (dec_count == 0 && num != 0)
		return (ft_strdup("0"));
	return (get_str_int_part(num, dec_count, is_negative));
}

static void	round_last_rank(char **output, long double rest)
{
	if (rest >= 5)
	{
		*output -= 1;
		if (**output < 9)
			**output += 1;
		else
			**output = '0';
	}
}

char		*ldtoa_rest_part(long double num, unsigned int precision)
{
	char *result;
	char *ptr;
	char *tmp;

	if (is_only_int(num))
		return (NULL);
	num = get_rest(num);
	result = ft_strnew(precision + 1);
	ptr = result;
	*ptr++ = '.';
	while (precision-- != 0)
	{
		num *= 10;
		tmp = ft_itoa((int)num);
		num -= (int)num;
		ft_strcpy(ptr++, tmp);
		free(tmp);
	}
	round_last_rank(&ptr, num * 10);
	return (result);
}

int			get_integer_part_decimal_count(long double f)
{
	int count;

	count = 0;
	f = f > 0 ? f : -f;
	while (f >= 1)
	{
		f /= 10;
		count++;
	}
	return (count);
}
