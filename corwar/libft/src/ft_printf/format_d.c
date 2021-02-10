/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:37:27 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 11:38:13 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*format_d(t_flag *flag, va_list ap)
{
	long long int	tmp;

	tmp = 0;
	if (ft_strequ(flag->format_mod, "l"))
		tmp = va_arg(ap, long);
	else if (ft_strequ(flag->format_mod, "ll"))
		tmp = va_arg(ap, long long);
	else if (ft_strequ(flag->format_mod, "h"))
		tmp = (short int)va_arg(ap, int);
	else if (ft_strequ(flag->format_mod, "hh"))
		tmp = (char)va_arg(ap, int);
	else if (ft_strequ(flag->format_mod, "z"))
		tmp = (int)va_arg(ap, long long int);
	else if (*flag->format_mod == 0)
		tmp = va_arg(ap, int);
	return (ft_itoa_long(tmp));
}
