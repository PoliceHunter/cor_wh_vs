/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:58:43 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/06 19:18:18 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s1 != NULL)
	{
		free(s1);
		s1 = NULL;
	}
	return (str);
}
