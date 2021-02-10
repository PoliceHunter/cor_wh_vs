/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:16:43 by tmyrcell          #+#    #+#             */
/*   Updated: 2021/02/09 12:16:44 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"

void	flag_visual(t_cor *cor, char *num, int ac, int *i)
{
	int	tmp;

	if (cor->flag.visual != 0)
		exterminate(cor, FEW_AC_V);
	if ((*i + 3) > ac)
		exterminate(cor, FEW_AC_V);
	*i += 2;
	tmp = ft_atoi(num);
	if (tmp > INT_MAX || tmp <= 0)
		exterminate(cor, INVALID_VISUAL);
	cor->flag.visual = tmp;
}

void	flag_aff(t_cor *cor, int ac, int *i)
{
	if (cor->flag.aff != 0)
		exterminate(cor, FEW_AC_V);
	if ((*i + 2) > ac)
		exterminate(cor, FEW_AC_V);
	cor->flag.aff = 1;
	*i += 1;
}

void	parse_flags(t_cor *cor, int ac, char **av)
{
	int i;

	i = 0;
	while (++i < ac)
	{
		init_players(cor);
		check_dump_flag(cor, av, &i, ac);
		if (ft_strcmp(av[i], "-visual") == 0)
			flag_visual(cor, av[i + 1], ac, &i);
		if (ft_strcmp(av[i], "-aff") == 0)
			flag_aff(cor, ac, &i);
		if (!ft_strcmp(av[i], "-n") || is_filename(av[i], ".cor"))
		{
			if (ft_strcmp(av[i], "-n") == 0)
				save_num_player(cor, av[i + 1], &i, ac);
			else
				save_empty_num_player(cor, &i);
			cor->count_players++;
			if (cor->count_players > MAX_PLAYERS)
				exterminate(cor, TOO_MANY_PLAYERS);
		}
		else if (!is_filename(av[i], ".cor"))
			exterminate(cor, INVALID_PARAM);
	}
	cor->count_cursors = cor->count_players;
}
