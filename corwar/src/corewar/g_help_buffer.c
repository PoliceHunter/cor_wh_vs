/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljacquet <ljacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:56:21 by ljacquet          #+#    #+#             */
/*   Updated: 2020/12/18 14:48:30 by ljacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"
#include "../../includes/g_corewar_op.h"

void		make_buffer_codes(t_cor *cor)
{
	int		i;

	i = 0;
	cor->buffer_codes = (int *)malloc(sizeof(int) * 4);
	while (i < 4)
	{
		cor->buffer_codes[i] = 0;
		i++;
	}
	i = 0;
	cor->buffer_sizes = (int *)malloc(sizeof(int) * 4);
	while (i < 4)
	{
		cor->buffer_sizes[i] = 0;
		i++;
	}
}

void		fill_buffer_with_zeros(t_cor *cor)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		cor->buffer_codes[i] = 0;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		cor->buffer_sizes[i] = 0;
		i++;
	}
}

int			is_reg(t_cor *cor, t_process *process, int32_t step)
{
	int8_t	r_id;

	r_id = cor->map[get_address(process, step, 0)];
	if (r_id >= 1 && r_id <= REG_NUMBER)
		return (1);
	else
		return (0);
}
