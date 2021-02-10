/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:41:26 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 11:41:54 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*format_x(t_flag *flag, va_list ap)
{
	char *length_x;

	length_x = NULL;
	if (chk_lng(flag) == 'z')
		length_x = ft_itoa_base((unsigned int)va_arg(ap, long int), 16);
	else if (chk_lng(flag) == 'l')
		length_x = ft_itoa_base((unsigned long)va_arg(ap, long int), 16);
	else if (chk_lng(flag) == 'm')
		length_x = ft_itoa_base((unsigned long)va_arg(ap, long long int), 16);
	else if (chk_lng(flag) == 'h')
		length_x = ft_itoa_base((short unsigned int)va_arg(ap, int), 16);
	else if (chk_lng(flag) == 'i')
		length_x = ft_itoa_base((unsigned char)va_arg(ap, int), 16);
	if (ft_strcmp("0", length_x) == 0 && flag->precision == 0
			&& flag->is_dot == 1)
	{
		free(length_x);
		return (ft_strdup(""));
	}
	return (length_x);
}
