/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:41:04 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/23 19:41:40 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strndup(const char *src, size_t len)
{
	char	*ret;

	ret = malloc(len + 1);
	ft_bzero(ret, len + 1);
	if (!ret)
		return (NULL);
	ft_strncpy(ret, src, len);
	return (ret);
}
