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

void	dublicate_process(t_process *dubl, t_process *proc)
{
	int	index;

	index = -1;
	while (++index < REG_NUMBER)
		dubl->reg[index] = proc->reg[index];
	dubl->carry = proc->carry;
	dubl->live_last_cycle = proc->live_last_cycle;
	dubl->live_last_id = proc->live_last_id;
}

void	g_fork(t_cor *cor, t_process *proc)
{
	int32_t		arg1;
	int32_t		address;
	t_process	*dubl;

	arg1 = get_value(cor, proc, 0);
	address = get_address(proc, arg1 % IDX_MOD, 0);
	dubl = init_process(address, cor->process, proc->player_id);
	dublicate_process(dubl, proc);
	dubl->id = ((t_process *)get_from_vec(&cor->process, 0))->id + 1;
	push_front_vec(&cor->process, dubl);
	free(dubl);
	cor->count_cursors++;
}
