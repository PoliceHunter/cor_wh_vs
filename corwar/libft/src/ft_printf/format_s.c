/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:39:50 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 11:40:15 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*format_s(va_list ap)
{
	char *res;

	res = va_arg(ap, char*);
	if (res == NULL)
		res = ft_strdup("(null)");
	else
		res = ft_strdup(res);
	return (res);
}
