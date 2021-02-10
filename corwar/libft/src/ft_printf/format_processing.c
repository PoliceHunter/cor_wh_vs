/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:43:30 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/22 17:07:11 by jczech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*find_coincidence(t_flag *flag, va_list ap)
{
	if (!(ft_strcmp(flag->format, "d")))
		return (format_d(flag, ap));
	else if (!(ft_strcmp(flag->format, "c"))
			|| (!(ft_strcmp(flag->format, "C"))))
		return (format_c(flag, ap));
	else if (!(ft_strcmp(flag->format, "s")))
		return (format_s(ap));
	else if (!(ft_strcmp(flag->format, "f")))
		return (format_f(flag, ap));
	else if (!(ft_strcmp(flag->format, "u")))
		return (format_u(flag, ap));
	else if (!(ft_strcmp(flag->format, "p")))
		return (format_p(ap));
	else if (!(ft_strcmp(flag->format, "x")))
		return (format_x(flag, ap));
	else if (!(ft_strcmp(flag->format, "X")))
		return (format_xx(flag, ap));
	else if (!(ft_strcmp(flag->format, "o")))
		return (format_o(flag, ap));
	else if (!(ft_strcmp(flag->format, "%")))
		return (ft_strdup("%"));
	return (NULL);
}

char	*format_processing(t_flag *flag, va_list ap)
{
	char *tmp;

	tmp = find_coincidence(flag, ap);
	tmp = overlay_flags(flag, tmp);
	return (tmp);
}
