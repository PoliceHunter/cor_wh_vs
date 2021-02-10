/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:29:29 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 11:33:15 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static	void	initialize_with_zero(t_flag *flag)
{
	flag->flag_minus = 0;
	flag->flag_plus = 0;
	flag->flag_zero = 0;
	flag->flag_space = 0;
	flag->flag_hash = 0;
	flag->width = 1;
	flag->precision = 0;
	flag->is_dot = 0;
	flag->format = ft_strnew(1);
	flag->format_mod = ft_strnew(3);
}

t_flag			*ft_analyze_format(char *stringformat, t_flag *flag, va_list ap)
{
	int index;

	index = 0;
	initialize_with_zero(flag);
	while (*stringformat)
	{
		analyze_flags(*stringformat, flag, ap);
		analyze_precision(&stringformat, flag, ap);
		if (ft_isdigit(*stringformat) && *stringformat != '0')
		{
			flag->width = ft_atoi(stringformat);
			while (ft_isdigit(*stringformat))
				stringformat++;
			continue;
		}
		while (*stringformat && ft_strchr(MODSCHAR, *stringformat))
		{
			(flag->format_mod)[index++] = *stringformat;
			stringformat++;
		}
		if (analyze_specifiers(stringformat, flag))
			return (flag);
		stringformat++;
	}
	return (NULL);
}
