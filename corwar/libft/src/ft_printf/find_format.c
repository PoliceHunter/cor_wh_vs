/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:34:31 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/22 17:03:14 by jczech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static int	ft_if_supported(char *stringformat)
{
	size_t index;

	index = 0;
	if (!stringformat)
		return (0);
	while (stringformat[index])
	{
		if (!ft_strchr(SUPPORTED, stringformat[index]))
			return (0);
		index++;
	}
	return (1);
}

static void	free_struct(t_flag *flag)
{
	if (flag->format)
		free(flag->format);
	if (flag->format_mod)
		free(flag->format_mod);
	free(flag);
}

int			ft_find_format(
	const char **format,
	char **output,
	va_list ap,
	unsigned int *mod_size)
{
	size_t		size;
	char		*stringformat;
	t_flag		*flag;

	*format += 1;
	stringformat = NULL;
	flag = (t_flag *)malloc(sizeof(t_flag));
	*mod_size = ft_get_mods(*format, &stringformat);
	if (!(ft_if_supported(stringformat)) || stringformat == 0)
	{
		free(flag);
		if (stringformat)
			free(stringformat);
		return (-1);
	}
	ft_analyze_format(stringformat, flag, ap);
	*output = format_processing(flag, ap);
	size = strlen_bytes(*output, flag);
	free(stringformat);
	free_struct(flag);
	return (size);
}
