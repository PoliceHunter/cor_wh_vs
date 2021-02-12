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
#include "../../includes/visual.h"

int32_t		calc_addr(int32_t addr)
{
	addr %= MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}

void		update_map(t_cor *vm, t_process *cursor, int32_t addr, int32_t size)
{
	int32_t value;

	value = ((cursor->player_id - 1) % MAX_PLAYER_ID) + 1;
	while (size)
	{
		vm->vs->map[calc_addr(addr + size - 1)].index = value;
		vm->vs->map[calc_addr(addr
							  + size - 1)].wait_cycles_store = CYCLE_TO_WAIT;
		size--;
	}
}

void				st(t_cor *cor, t_process *proc)
{
	int32_t	reg1num;
	int32_t	reg2num;
	int32_t	regvalue;
	int32_t	address;
	int32_t	arg2;

	reg1num = cor->map[get_address(proc, 2, 0)];
	regvalue = proc->reg[reg1num - 1];
	if (cor->buffer_codes[1] == REG_CODE)
	{
		reg2num = cor->map[get_address(proc, get_step(cor, proc, 1), 0)];
		proc->reg[reg2num - 1] = regvalue;
	}
	if (cor->buffer_codes[1] == IND_CODE)
	{
		arg2 = byte_to_int32(cor, proc, 1, cor->buffer_sizes[1]);
		address = get_address(proc, arg2 % IDX_MOD, 0);
		value32_to_map(cor, regvalue, address, DIR_SIZE);
		if (cor->vs)
			update_map(cor, proc, proc->pos + (address % IDX_MOD), DIR_SIZE);
	}
}
