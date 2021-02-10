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

void				sti(t_cor *cor, t_process *proc)
{
	int32_t			regvalue;
	int32_t			value2;
	int32_t			value3;
	int32_t			address;

	regvalue = get_value(cor, proc, 0);
	value2 = get_value(cor, proc, 1);
	value3 = get_value(cor, proc, 2);
	address = get_address(proc, (value2 + value3) % IDX_MOD, 0);
	value32_to_map(cor, regvalue, address, DIR_SIZE);
}
