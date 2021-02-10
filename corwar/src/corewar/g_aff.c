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

void				aff(t_cor *cor, t_process *proc)
{
	int32_t	regnum1;
	int32_t	value;

	regnum1 = get_value(cor, proc, 0);
	value = proc->reg[regnum1 - 1];
	if (cor->flag.aff)
		ft_printf("Aff: %c\n", (char)value);
}
