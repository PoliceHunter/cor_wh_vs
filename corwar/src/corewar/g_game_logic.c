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

void			parse_codetype(t_cor *cor, t_process *process)
{
	int8_t		type_code;
	int			i;

	i = 0;
	fill_buffer_with_zeros(cor);
	g_sizes[1] = g_op[process->real_op_code].dir_size;
	type_code = cor->map[get_address(process, 1, 0)];
	process->op_step = 1 + g_op[process->real_op_code].args_types_code;
	while (i < g_op[process->real_op_code].args_num)
	{
		if (g_op[process->real_op_code].args_types_code == 0)
		{
			cor->buffer_codes[i] = g_op[process->real_op_code].args_codes1[i];
			cor->buffer_sizes[i] = g_sizes[cor->buffer_codes[i] - 1];
			process->op_step = process->op_step + cor->buffer_sizes[i];
		}
		else
		{
			cor->buffer_codes[i] = (type_code & g_calc[i]) >> g_sdvig[i];
			cor->buffer_sizes[i] = g_sizes[cor->buffer_codes[i] - 1];
			process->op_step = process->op_step + cor->buffer_sizes[i];
		}
		i++;
	}
}

void			kill_caretka(t_cor *cor)
{
	t_process	*process;
	int			index;

	index = -1;
	while (++index < cor->count_cursors)
	{
		process = get_from_vec(&cor->process, index);
		if (process->live_last_cycle == -1 || cor->cycles_to_die <= 0)
		{
			if (cor->flag.visual == 4)
				clear_cursor(cor, process);
			print_log(cor, process, 2);
			remove_from_vec(&cor->process, index);
			cor->count_cursors--;
			index--;
		}
		else
			process->live_last_cycle = -1;
	}
}

static void		reset_lives_nums(t_cor *vm)
{
	int32_t		i;

	i = 0;
	while (i < vm->count_players - 1)
	{
		vm->player[i].previous_lives_num = vm->player[i].current_lives_num;
		vm->player[i].current_lives_num = 0;
		i++;
	}
	vm->count_lives = 0;
}

void			make_check(t_cor *cor)
{
	cor->count_check++;
	kill_caretka(cor);
	if (cor->count_lives >= NBR_LIVE || cor->count_check == MAX_CHECKS)
	{
		cor->cycles_to_die -= CYCLE_DELTA;
		cor->count_check = 0;
	}
	reset_lives_nums(cor);
	cor->cycles_after_check = 0;
	cor->count_lives = 0;
}

int				process_game_logic(t_cor *cor)
{
	cor->cycles_to_die = CYCLE_TO_DIE;
	while (cor->count_cursors > 0)
	{
		check_flag(cor);
		cor->cycle++;
		game_in_cycle(cor);
		cor->cycles_after_check++;
		if (cor->cycles_to_die == cor->cycles_after_check
		|| cor->cycles_to_die <= 0)
			make_check(cor);
	}
	return (1);
}
