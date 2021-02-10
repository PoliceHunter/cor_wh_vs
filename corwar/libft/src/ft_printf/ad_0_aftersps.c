/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ad_0_aftersps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jczech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 16:51:18 by jczech            #+#    #+#             */
/*   Updated: 2020/02/22 16:52:15 by jczech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

char	*fill_0_after_space(char *input, unsigned int count)
{
	int		i;
	char	*buffer;

	i = 0;
	if (!(buffer = (char *)malloc(sizeof(char) * (ft_strlen(input) + count) +
					1)))
	{
		free(input);
		return (0);
	}
	if (input[0] == '-' || input[0] == '+' || input[0] == ' ')
	{
		buffer[0] = input[0];
		i = 1;
	}
	ft_fill_by_symbol(buffer + i, count, '0');
	ft_strcpy(buffer + count + i, input + i);
	free(input);
	return (buffer);
}
