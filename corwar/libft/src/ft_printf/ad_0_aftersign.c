/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ad_0_aftersign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:27:07 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 11:27:28 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*ad_0_aftersign(char *s, unsigned int n)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(s) + n) + 1)))
		return (0);
	if (s[0] == '-' || s[0] == '+')
	{
		new[0] = s[0];
		j++;
		i++;
	}
	while (n != 0)
	{
		new[j] = '0';
		n--;
		j++;
	}
	while (s[i])
		new[j++] = s[i++];
	new[j] = 0;
	free(s);
	return (new);
}
