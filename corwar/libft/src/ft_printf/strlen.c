/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:06:43 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/22 17:34:18 by jczech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

unsigned int	len_without_x(const char *s)
{
	int i;

	i = ft_strlen(s);
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		return (i - 2);
	return (i);
}

unsigned int	len_without_spec(const char *s)
{
	int i;

	i = ft_strlen(s);
	if (s[0] == '-' || s[0] == '+' || s[0] == ' ')
		return (i - 1);
	return (i);
}

unsigned int	len_without_sign(const char *s)
{
	int i;

	i = ft_strlen(s);
	if (s[0] == '-' || s[0] == '+')
		return (i - 1);
	return (i);
}

unsigned long	strlen_bytes(char *input, t_flag *flag)
{
	int is_additional_zero;
	int offset;

	is_additional_zero = flag->format[0] == 'c' && flag->flag_zero == 2;
	offset = flag->flag_minus ? is_additional_zero : 0;
	return (ft_strlen(input + offset) + is_additional_zero);
}
