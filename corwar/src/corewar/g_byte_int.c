/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljacquet <ljacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:56:21 by ljacquet          #+#    #+#             */
/*   Updated: 2021/02/09 12:54:19 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"
#include "../../includes/g_corewar_op.h"

int32_t			byte_to_int32(t_cor *cor, t_process *process, int i1, int size)
{
	int32_t		res;
	int			znak;
	int			i;

	res = 0;
	znak = 0;
	if ((cor->map[get_address(process, get_step(cor, process, i1), 0)]
		& 0x80) >> 7 == 1)
		znak = 1;
	i = 0;
	while (size)
	{
		if (znak == 1)
			res = res + ((cor->map[get_address(process,
				get_step(cor, process, i1) + size - 1, 0)] ^ 0xFF)
					<< (i++ * 8));
		else
			res = res + (cor->map[get_address(process, get_step(cor,
				process, i1) + size - 1, 0)] << (i++ * 8));
		size--;
	}
	if (znak == 1)
		res = ~(res);
	return (res);
}

int32_t			byte_to_int32_2(t_cor *cor, uint32_t address, int size)
{
	int32_t		res;
	int			znak;
	int			i;

	res = 0;
	znak = 0;
	if ((cor->map[address] & 0x80) >> 7 == 1)
		znak = 1;
	i = 0;
	while (size)
	{
		if (znak == 1)
			res = res + ((cor->map[get_address_map(address, size - 1)]
				^ 0xFF) << (i++ * 8));
		else
			res = res + (cor->map[get_address_map(address, size - 1)]
					<< (i++ * 8));
		size--;
	}
	if (znak == 1)
		res = ~(res);
	return (res);
}

void			value32_to_map(t_cor *cor, int32_t val,
	uint32_t address, int size)
{
	uint32_t	i;
	uint32_t	finaddr;

	i = 0;
	while (size)
	{
		finaddr = address + size - 1;
		if (finaddr >= MEM_SIZE)
			finaddr = finaddr % MEM_SIZE;
		cor->map[finaddr] = (uint8_t)((val >> i) & 0xFF);
		i += 8;
		size--;
	}
}
