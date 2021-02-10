/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 15:36:55 by tmyrcell          #+#    #+#             */
/*   Updated: 2019/10/18 19:50:11 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *src)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (NULL);
	tmp = ft_strcpy(tmp, src);
	return (tmp);
}
