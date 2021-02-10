/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_flags_with_per.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:13:21 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 12:14:05 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*work_flags_with_per(t_flag *flag, char *tmp)
{
	int	count;

	count = flag->width;
	if (flag->flag_minus == 1)
		while (count > 1)
		{
			tmp = ft_strjoin_free(tmp, " ");
			count--;
		}
	else if (flag->flag_zero == 1)
		while (count > 1)
		{
			tmp = ft_strjoin_free2("0", tmp);
			count--;
		}
	else if (flag->width >= 2)
		while (count > 1)
		{
			tmp = ft_strjoin_free2(" ", tmp);
			count--;
		}
	return (tmp);
}
