/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inscrem_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jczech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 17:12:59 by jczech            #+#    #+#             */
/*   Updated: 2020/02/23 19:26:33 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static void		part_2(char *tmp, unsigned int precis, unsigned int i)
{
	int flag;

	flag = 1;
	while (flag == 1)
	{
		if (tmp[i + precis] == '.')
			i--;
		if (tmp[i + precis] == '9')
		{
			tmp[i + precis] = '0';
			flag = 1;
		}
		else
		{
			tmp[i + precis]++;
			flag = 0;
		}
		i--;
	}
}

void			increm_s(char *str, unsigned int precis)
{
	unsigned int i;

	i = 0;
	while (str[i] != '.')
		i++;
	if (ft_strlen(str) == i)
		return ;
	if (str[i + precis + 1] >= '5')
	{
		if (str[i + precis] == '.')
			i--;
		if (str[i + precis] + 1 < '9')
			str[i + precis]++;
		else
			part_2(str, precis, i);
	}
}
