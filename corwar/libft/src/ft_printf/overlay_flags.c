/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:05:03 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/22 17:30:18 by jczech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*overlay_flags(t_flag *flag, char *tmp)
{
	if (tmp == NULL)
		return (NULL);
	if (flag->format[0] == 'c')
		return (tmp);
	if (flag->format[0] == 'd')
		tmp = work_flags_with_d(flag, tmp);
	if (flag->format[0] == 's')
		tmp = work_flags_with_s(flag, tmp);
	if (flag->format[0] == 'f')
		tmp = work_flags_with_f(flag, tmp);
	if (flag->format[0] == 'u')
		tmp = work_flags_with_u(flag, tmp);
	if (flag->format[0] == 'p')
		tmp = work_flags_with_p(flag, tmp);
	if (flag->format[0] == 'x' || flag->format[0] == 'X')
		tmp = work_flags_with_x(flag, tmp);
	if (flag->format[0] == 'o')
		tmp = work_flags_with_o(flag, tmp);
	if (flag->format[0] == '%')
		tmp = (char *)work_flags_with_per(flag, tmp);
	return (tmp);
}
