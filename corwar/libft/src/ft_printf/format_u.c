/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:40:22 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 11:41:20 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*format_u(t_flag *flag, va_list ap)
{
	char *length_u;

	length_u = NULL;
	if (chk_lng(flag) == 'z')
		length_u = ft_itoa_unsigned_long((unsigned int)va_arg(ap, int));
	else if (chk_lng(flag) == 'l')
		length_u = ft_itoa_unsigned_long((unsigned long int)va_arg(ap, long));
	else if (chk_lng(flag) == 'm')
		length_u = ft_itoa_unsigned_long((unsigned long int)va_arg(ap, long));
	else if (chk_lng(flag) == 'h')
		length_u = ft_itoa_long((short unsigned int)va_arg(ap, long));
	else if (chk_lng(flag) == 'i')
		length_u = ft_itoa_long((unsigned char)va_arg(ap, long));
	if (ft_strcmp("0", length_u) == 0 && flag->precision == 0
			&& flag->is_dot == 1)
	{
		free(length_u);
		return (ft_strdup(""));
	}
	return (length_u);
}
