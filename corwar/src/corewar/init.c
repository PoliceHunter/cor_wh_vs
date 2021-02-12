/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:02:07 by tmyrcell          #+#    #+#             */
/*   Updated: 2021/02/09 12:02:09 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"

void		init_players(t_cor *cor)
{
	cor->player[cor->count_players].name = NULL;
	cor->player[cor->count_players].code = NULL;
	cor->player[cor->count_players].comment = NULL;
	cor->player[cor->count_players].position_on_map = 0;
	cor->player[cor->count_players].index_player_ac = 0;
	cor->player[cor->count_players].id = 0;
	cor->player[cor->count_players].code_size = 0;
	cor->player[cor->count_players].current_lives_num = 0;
	cor->player[cor->count_players].previous_lives_num = 0;
}

void		init_cor(t_cor *cor, char **av)
{
	cor->cycles_to_die = CYCLE_TO_DIE;
	cor->files = av;
	cor->count_players = 0;
	cor->flag.visual = 0;
	cor->flag.dump32 = 0;
	cor->flag.dump64 = 0;
	cor->flag.aff = 0;
	cor->count_cursors = 0;
	cor->cycle = 0;
	cor->cycles_after_check = 0;
	cor->count_check = 0;
	cor->last_live_player = 0;
	cor->buffer_codes = NULL;
	make_buffer_codes(cor);
	cor->count_lives = 0;
	cor->count_players = 0;
	cor->process.data = NULL;
	cor->vs = NULL;
}

void		init_arena(t_cor *cor)
{
	int			index;
	uint32_t	pos;

	pos = 0;
	index = -1;
	while (++index != MEM_SIZE)
		cor->map[index] = 0;
	index = -1;
	while (++index != cor->count_players)
	{
		ft_memcpy(&(cor->map[pos]), cor->player[index].code,
			(size_t)cor->player[index].code_size);
		cor->player[index].position_on_map = pos;
		pos += MEM_SIZE / cor->count_players;
	}
}

t_process	*init_process(int32_t pos, t_vector process, int player_id)
{
	t_process	*proc;
	int			i;

	i = 1;
	proc = malloc(sizeof(t_process));
	proc->carry = FALSE;
	proc->cycle_to_exec = 0;
	proc->live_last_cycle = -1;
	proc->live_last_id = 0;
	proc->pos = pos;
	proc->op_step = 0;
	proc->op_code = 0;
	proc->real_op_code = 0;
	proc->id = process.size + 1;
	proc->player_id = player_id;
	proc->reg[0] = -player_id;
	while (i < 16)
		proc->reg[i++] = 0;
	return (proc);
}

void		init_processes(t_cor *cor)
{
	int			index;
	int32_t		pos;
	t_vector	process;
	t_process	*tmp;

	pos = 0;
	process = new_vector(cor->count_cursors, sizeof(t_process));
	index = -1;
	while (++index != cor->count_cursors)
	{
		tmp = init_process(pos, process, cor->player[index].id);
		push_front_vec(&process, tmp);
		free(tmp);
		pos += MEM_SIZE / cor->count_players;
	}
	cor->process = process;
}
