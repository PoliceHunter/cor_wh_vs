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

void				zjmp(t_cor *cor, t_process *proc)
{
	int32_t			arg1;
	int32_t			jump;

	arg1 = byte_to_int32(cor, proc, 0, cor->buffer_sizes[0]);
	jump = arg1 % IDX_MOD;
	if (proc->carry == 1)
		proc->op_step = jump;
}
