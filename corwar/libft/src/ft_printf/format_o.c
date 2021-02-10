/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:38:26 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 11:38:49 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*format_o(t_flag *flag, va_list ap)
{
	unsigned long long int a;

	a = 0;
	if (ft_strequ(flag->format_mod, "l"))
		a = va_arg(ap, long);
	else if (ft_strequ(flag->format_mod, "ll"))
		a = va_arg(ap, long);
	else if (ft_strequ(flag->format_mod, "h"))
		a = (unsigned short int)va_arg(ap, long);
	else if (ft_strequ(flag->format_mod, "hh"))
		a = (unsigned char)va_arg(ap, long);
	else if (*flag->format_mod == 0)
		a = (unsigned int)va_arg(ap, int);
	if (a == 0)
		return (ft_strdup("0"));
	return (ft_itoa_base(a, 8));
}
