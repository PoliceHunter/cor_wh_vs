/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:36:33 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/23 20:01:12 by jczech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static char	*fill_symbol_for_c(char *input, int space_count, char chr,
		int is_begin)
{
	ft_fill_by_symbol(input, space_count, ' ');
	input[is_begin ? 0 : space_count] = chr;
	if (!is_begin)
		input[space_count + 1] = 0;
	return (input);
}

static char	*mem_for_c(t_flag *flag, char *tmp)
{
	if (flag->width != 1)
		tmp = malloc(sizeof(char *) * (flag->width + 1));
	else
		tmp = malloc(sizeof(char *) * 2);
	return (tmp);
}

static char	*fill_by_width(t_flag *flag, char *tmp, char chr)
{
	if (flag->flag_minus == 1)
		tmp = fill_symbol_for_c(tmp, flag->width, chr, 1);
	else
		tmp = fill_symbol_for_c(tmp, flag->width - 1, chr, 0);
	return (tmp);
}

char		*format_c(t_flag *flag, va_list ap)
{
	char *tmp;
	char chr;

	tmp = NULL;
	chr = (char)va_arg(ap, int);
	tmp = mem_for_c(flag, tmp);
	if (flag->flag_zero == 1 && flag->flag_minus == 0)
	{
		if (flag->width > 1)
			tmp = fill_0_after_space(tmp, flag->width - 1);
	}
	else if (flag->width > 1)
		tmp = fill_by_width(flag, tmp, chr);
	if (flag->width < 2)
	{
		tmp[0] = chr;
		tmp[1] = 0;
	}
	if (chr == 0)
		flag->flag_zero = 2;
	return (tmp);
}

char		*ft_fill_by_symbol(char *s, unsigned int symbol_count, char symbol)
{
	unsigned int j;

	j = 0;
	while (j != symbol_count)
		s[j++] = symbol;
	s[j] = 0;
	return (s);
}
