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

void				lld(t_cor *cor, t_process *proc)
{
	int32_t			reg2;
	int32_t			value_to_reg;

	value_to_reg = get_value(cor, proc, 0);
	if (value_to_reg == MEM_SIZE + 1)
		return ;
	reg2 = get_value(cor, proc, 1);
	proc->reg[reg2 - 1] = value_to_reg;
	if (value_to_reg == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
}
