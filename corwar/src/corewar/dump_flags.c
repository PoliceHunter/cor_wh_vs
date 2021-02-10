/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:31:47 by tmyrcell          #+#    #+#             */
/*   Updated: 2021/02/09 12:31:49 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"

void	parse_dump_flag(t_cor *cor, char *num, int *i, int ac)
{
	long tmp;

	if (cor->flag.dump32 != 0 || cor->flag.dump64 != 0)
		exterminate(cor, FEW_AC_DUMP);
	if ((*i + 3) > ac)
		exterminate(cor, FEW_AC_DUMP);
	*i += 2;
	tmp = ft_atol(num);
	if (tmp > INT_MAX || tmp < 0)
		exterminate(cor, INVALID_FLAG_D);
	cor->flag.dump32 = (int)tmp;
}

void	parse_d_flag(t_cor *cor, char *num, int *i, int ac)
{
	long tmp;

	if (cor->flag.dump64 != 0 || cor->flag.dump32 != 0)
		exterminate(cor, FEW_AC_DUMP);
	if ((*i + 3) > ac)
		exterminate(cor, FEW_AC_DUMP);
	*i += 2;
	tmp = ft_atol(num);
	if (tmp > INT_MAX || tmp < 0)
		exterminate(cor, INVALID_FLAG_D);
	cor->flag.dump64 = (int)tmp;
}

void	check_dump_flag(t_cor *cor, char **av, int *i, int ac)
{
	int index;

	index = *i;
	if (ft_strcmp(av[index], "-h") == 0)
		error_usage();
	if (ft_strcmp(av[index], "-dump") == 0)
	{
		parse_dump_flag(cor, av[index + 1], &index, ac);
		*i += 2;
	}
	if (ft_strcmp(av[index], "-d") == 0)
	{
		parse_d_flag(cor, av[index + 1], &index, ac);
		*i += 2;
	}
}

int		check_flag(t_cor *cor)
{
	if (cor->flag.dump64 == (int)cor->cycle && cor->flag.dump64 != 0)
	{
		print_arena(cor->map, 64);
		free_vec(&cor->process);
		free_cor(cor);
		exit(0);
	}
	if (cor->flag.dump32 == (int)cor->cycle && cor->flag.dump32 != 0)
	{
		print_arena(cor->map, 32);
		free_vec(&cor->process);
		free_cor(cor);
		exit(0);
	}
	return (0);
}
