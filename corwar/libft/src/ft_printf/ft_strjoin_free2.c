/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:59:23 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 11:59:44 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*ft_strjoin_free2(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s2 != NULL)
		free(s2);
	return (str);
}
