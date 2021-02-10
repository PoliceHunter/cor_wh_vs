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

void				add(t_cor *cor, t_process *proc)
{
	int32_t valreg1;
	int32_t	valreg2;
	int32_t numreg3;
	int32_t value_to_reg;

	valreg1 = get_value(cor, proc, 0);
	valreg2 = get_value(cor, proc, 1);
	value_to_reg = valreg1 + valreg2;
	numreg3 = byte_to_int32(cor, proc, 2, cor->buffer_sizes[2]);
	proc->reg[numreg3 - 1] = value_to_reg;
	if (value_to_reg == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
}
