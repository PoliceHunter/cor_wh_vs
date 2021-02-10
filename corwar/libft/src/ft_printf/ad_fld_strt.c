/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ad_fld_strt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jczech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 16:52:51 by jczech            #+#    #+#             */
/*   Updated: 2020/02/22 16:53:55 by jczech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*add_fld_strt(char *s, unsigned int nb_space)
{
	int		i;
	char	*new;
	char	*temp;

	i = 0;
	if (!(temp = (char *)malloc(sizeof(char) * (nb_space + 1))))
		return (NULL);
	while (nb_space != 0)
	{
		temp[i] = ' ';
		i++;
		nb_space--;
	}
	temp[i] = 0;
	new = ft_strjoin(temp, s);
	ft_strdel(&temp);
	ft_strdel(&s);
	return (new);
}
