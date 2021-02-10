/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_af_dot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:33:22 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 11:34:25 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int		count_af_dot(char *tmp)
{
	int j;
	int count;

	j = 0;
	count = 0;
	if (is_s_dec(tmp) == 0)
		return (0);
	while (tmp[j] != '.')
		j++;
	j++;
	while (tmp[j])
	{
		j++;
		count++;
	}
	return (count);
}

int		is_s_dec(char *tmp)
{
	int i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '.')
			return (1);
		i++;
	}
	return (0);
}
