/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:11:34 by tmyrcell          #+#    #+#             */
/*   Updated: 2021/02/09 12:11:35 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"
#include "../../includes/visual.h"

void	start_game(t_cor *cor)
{
	int		index;

	index = -1;
	process_game_logic(cor);
	while (cor->last_live_player != 0 && ++index < cor->count_players)
		if (cor->player[index].id == cor->last_live_player)
			break ;
	if ((cor->flag.dump64 == 0 && cor->flag.dump32 == 0) ||
	cor->flag.dump32 > cor->cycle || cor->flag.dump64 > cor->cycle)
	{
		if (cor->last_live_player == 0)
		{
			index = 0;
			cor->last_live_player = cor->player[index].id;
		}
		ft_printf("Contestant %d, \"%s\", has won !\n",
			cor->last_live_player, cor->player[index].name);
	}
	free_cor(cor);
}

void	check_player_id(t_cor *cor)
{
	int index;

	index = -1;
	while (++index != cor->count_players)
	{
		if (cor->player[index].id > cor->count_players)
			exterminate(cor, INVALID_FLAG_N);
	}
}

int		main(int ac, char **av)
{
	t_cor cor;

	if (ac == 1)
		error_usage();
	init_cor(&cor, av);
	parse_flags(&cor, ac, av);
	check_player_id(&cor);
	parse_champion_file(&cor);
	update_player_num(&cor);
	init_arena(&cor);
	init_processes(&cor);
	print_intro(&cor);
	if (cor.flag.visual == 4)
		visual(&cor);
	else
		start_game(&cor);
	return (0);
}
