/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:32:50 by tmyrcell          #+#    #+#             */
/*   Updated: 2021/02/09 12:32:51 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"

int		check_duplicate_num(t_cor *cor, long tmp)
{
	int index;

	index = -1;
	while (++index < cor->count_players)
	{
		if (tmp == cor->player[index].id && tmp != 0)
			return (1);
	}
	return (0);
}

void	save_num_player(t_cor *cor, char *num, int *i, int ac)
{
	long	tmp;
	int		amount_players;

	amount_players = cor->count_players;
	if ((*i + 3) > ac)
		exterminate(cor, FEW_AC_N);
	*i += 2;
	tmp = ft_atol(num);
	if (tmp > MAX_PLAYERS || tmp <= 0)
		exterminate(cor, INVALID_FLAG_N);
	if (check_duplicate_num(cor, tmp))
		exterminate(cor, DUPLICATE_NUM_N);
	cor->player[amount_players].id = (int)tmp;
	cor->player[amount_players].index_player_ac = *i;
}

void	sort_players(t_cor *cor)
{
	t_player	tmp;
	int			index;
	int			j;

	index = -1;
	while (++index != cor->count_players - 1)
	{
		j = index + 1;
		while (j != cor->count_players)
		{
			if (cor->player[index].id > cor->player[j].id)
			{
				tmp = cor->player[index];
				cor->player[index] = cor->player[j];
				cor->player[j] = tmp;
				index = -1;
				break ;
			}
			j++;
		}
	}
}

void	update_player_num(t_cor *cor)
{
	int count;
	int index;

	index = 0;
	count = 1;
	if (cor->count_players != 0)
	{
		while (index < cor->count_players)
		{
			while (check_duplicate_num(cor, count))
			{
				count++;
				index = 0;
			}
			if (cor->player[index].id == 0)
			{
				cor->player[index].id = count;
				count++;
			}
			index++;
		}
	}
	sort_players(cor);
}

void	save_empty_num_player(t_cor *cor, const int *i)
{
	cor->player[cor->count_players].id = 0;
	cor->player[cor->count_players].index_player_ac = *i;
}
