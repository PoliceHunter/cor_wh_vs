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

int				arg_types(t_cor *cor, t_process *process)
{
	int32_t		i;
	int			bc;

	i = 0;
	while (i < g_op[process->real_op_code].args_num)
	{
		bc = cor->buffer_codes[i];
		if (bc == 0 || (bc != g_op[process->real_op_code].args_codes1[i] &&
			bc != g_op[process->real_op_code].args_codes2[i] &&
			bc != g_op[process->real_op_code].args_codes3[i]))
			return (0);
		i++;
	}
	return (1);
}

int				args_ok(t_cor *cor, t_process *process)
{
	int32_t		i;
	uint32_t	step;

	i = 0;
	step = (1 + (g_op[process->real_op_code].args_types_code ? 1 : 0));
	while (i < g_op[process->real_op_code].args_num)
	{
		if ((cor->buffer_codes[i] == T_REG)
			&& is_reg(cor, process, step) == 0)
			return (0);
		step += cor->buffer_sizes[i];
		i++;
	}
	return (1);
}

uint32_t		calc_next_step(t_cor *cor, t_process *process)
{
	int32_t		i;
	uint32_t	next_step;

	i = 0;
	next_step = 0;
	next_step += 1 + (g_op[process->real_op_code].args_types_code ? 1 : 0);
	while (i < g_op[process->real_op_code].args_num)
	{
		next_step += cor->buffer_sizes[i];
		i++;
	}
	return (next_step);
}

int				time_to_do(t_cor *cor, t_process *process, int index)
{
	int			temp;

	if (process->op_code >= 1 && process->op_code <= 16)
	{
		parse_codetype(cor, process);
		if (arg_types(cor, process) == 1 && args_ok(cor, process) == 1)
		{
			print_log(cor, process, 1);
			temp = process->op_code;
			g_op[process->real_op_code].func(cor, process);
			if (temp == 12)
				process = get_from_vec(&cor->process, ++index);
			process->next_step = process->op_step;
		}
		else
			process->next_step += calc_next_step(cor, process);
	}
	else
		process->next_step = 1;
	process->pos = get_address(process, process->next_step, 1);
	return (index);
}

void			game_in_cycle(t_cor *cor)
{
	int			index;
	t_process	*process;

	index = -1;
	while (++index < cor->count_cursors)
	{
		process = get_from_vec(&cor->process, index);
		if (process->cycle_to_exec == 0)
		{
			process->op_code = cor->map[process->pos];
			if (cor->map[process->pos] >= 1 && cor->map[process->pos] <= 16)
				process->cycle_to_exec = g_op[process->op_code - 1].cycles;
		}
		if (process->cycle_to_exec > 0)
			process->cycle_to_exec--;
		if (process->cycle_to_exec == 0)
		{
			process->real_op_code = -1;
			if (process->op_code >= 1 && process->op_code <= 16)
				process->real_op_code = process->op_code - 1;
			index = time_to_do(cor, process, index);
		}
	}
}
