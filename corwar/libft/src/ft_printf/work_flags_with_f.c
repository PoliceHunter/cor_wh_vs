/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_flags_with_f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jczech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 17:40:09 by jczech            #+#    #+#             */
/*   Updated: 2020/02/23 19:30:12 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static char		*add_space(char *input, unsigned int width, int is_right)
{
	char			*tmp;
	unsigned int	delta;
	unsigned int	len;

	len = ft_strlen(input);
	if (len < width)
	{
		delta = width - len;
		tmp = ft_fill_by_symbol(ft_strnew(delta), delta, ' ');
		if (is_right)
			input = ft_strjoin_free(input, tmp);
		else
			input = ft_strjoin_free2(tmp, input);
		free(tmp);
	}
	return (input);
}

static char		*add_zero_left(char *input, unsigned int width)
{
	char			*tmp;
	unsigned int	delta;

	delta = ft_strlen(input) - width;
	if (delta != 0)
	{
		tmp = ft_fill_by_symbol(ft_strnew(delta), delta, '0');
		input = ft_strjoin_free2(tmp, input);
		free(tmp);
	}
	return (input);
}

char			*work_flags_with_f(t_flag *flag, char *output)
{
	if (flag->flag_plus)
		output = ft_strjoin_free2("+", output);
	if (flag->is_dot == 1 && !flag->precision)
		output = ft_strsub_free(output, 0, ft_strchr(output, '.') - output);
	if (flag->flag_minus)
		output = add_space(output, flag->width, 1);
	else if (flag->flag_zero && !flag->flag_minus)
		output = add_zero_left(output, flag->width);
	else
		output = add_space(output, flag->width, 0);
	return (output);
}
