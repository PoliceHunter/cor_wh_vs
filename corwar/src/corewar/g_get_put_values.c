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

int32_t			get_step(t_cor *cor, t_process *proc, int i)
{
	int			i1;
	int32_t		begin;

	i1 = 0;
	begin = 0;
	while (i1 < i)
	{
		begin = begin + cor->buffer_sizes[i1];
		i1++;
	}
	begin = begin + 1 + g_op[proc->real_op_code].args_types_code;
	return (begin);
}

int32_t			get_value(t_cor *cor, t_process *proc, int i)
{
	int32_t		res;
	int			num;
	int32_t		addr;

	res = 0;
	if (cor->buffer_codes[i] == REG_CODE)
	{
		num = byte_to_int32(cor, proc, i, cor->buffer_sizes[i]);
		res = proc->reg[num - 1];
	}
	else if (cor->buffer_codes[i] == DIR_CODE)
	{
		res = byte_to_int32(cor, proc, i, cor->buffer_sizes[i]);
	}
	else if (cor->buffer_codes[i] == IND_CODE)
	{
		num = byte_to_int32(cor, proc, i, cor->buffer_sizes[i]);
		if (g_op[proc->real_op_code].op_code != 13
			&& g_op[proc->real_op_code].op_code != 14)
			addr = get_address(proc, num % IDX_MOD, 0);
		else
			addr = get_address(proc, num, 0);
		res = byte_to_int32_2(cor, addr, 4);
	}
	return (res);
}

int32_t			get_address(t_process *process, int32_t step, int key)
{
	int32_t		address;
	int32_t		delta;

	delta = process->pos + step;
	if (delta < 0)
	{
		if (delta < -MEM_SIZE)
			delta = delta % MEM_SIZE;
		address = MEM_SIZE + delta;
	}
	else
		address = process->pos + step;
	if (address >= MEM_SIZE)
		address = address % MEM_SIZE;
	if (key == 1)
		process->cycle_to_exec = 0;
	process->next_step = 0;
	return (address);
}

int32_t			get_address_map(int32_t address, int32_t step)
{
	int32_t		address2;
	int32_t		delta;

	delta = address + step;
	if (delta < 0)
		address2 = MEM_SIZE + delta;
	else
		address2 = address + step;
	if (address2 > MEM_SIZE)
		address2 = address2 % MEM_SIZE;
	return (address2);
}
