/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:48:06 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/23 19:40:36 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *left, char const *right)
{
	char	*result;
	size_t	left_len;
	size_t	right_len;

	left_len = ft_strlen(left);
	right_len = ft_strlen(right);
	if ((left_len + right_len) == 0)
		return (NULL);
	result = malloc((left_len + right_len + 1) * sizeof(char));
	memmove(result, left, left_len * sizeof(char));
	memmove(result + (left_len * sizeof(char)), right,
			(right_len + 1) * sizeof(char));
	return (result);
}
