/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mods.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:02:36 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/21 12:04:28 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static int	ft_is_mod(char c, char *formatlist)
{
	while (*formatlist)
	{
		if (c == *formatlist++)
			return (1);
	}
	return (0);
}

int			ft_get_mods(const char *format, char **stringformat)
{
	int		result;
	int		index;
	char	*formatlist;

	result = 0;
	formatlist = ft_strdup(SPECIFIERS);
	index = 0;
	while (format[index])
	{
		if ((result = ft_is_mod(format[index], formatlist)))
		{
			index++;
			*stringformat = ft_strndup(format, index);
			result = 1;
			break ;
		}
		index++;
	}
	free(formatlist);
	if (result == 0 && (!*format))
		return (result);
	return (index);
}
