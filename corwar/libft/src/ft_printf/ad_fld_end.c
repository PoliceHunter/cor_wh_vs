/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ad_fld_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:28:13 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 11:28:38 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*ad_fld_end(char *s, unsigned int nb_space)
{
	char *temp;
	char *new;

	new = NULL;
	if (!(temp = (char *)malloc(sizeof(char) * (nb_space + 1))))
		return (NULL);
	temp[nb_space] = 0;
	while (nb_space != 0)
	{
		temp[nb_space - 1] = ' ';
		nb_space--;
	}
	new = ft_strjoin(s, temp);
	ft_strdel(&temp);
	ft_strdel(&s);
	return (new);
}
