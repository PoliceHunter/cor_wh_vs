/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:08:06 by tmyrcell          #+#    #+#             */
/*   Updated: 2021/02/09 12:08:08 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"

void	free_cor(t_cor *cor)
{
	int i;

	i = -1;
	while (++i != cor->count_players)
	{
		if (cor->player[i].name != NULL)
			free(cor->player[i].name);
		if (cor->player[i].code != NULL)
			free(cor->player[i].code);
		if (cor->player[i].comment != NULL)
			free(cor->player[i].comment);
	}
	if (cor->process.data != NULL)
		free_vec(&cor->process);
	if (cor->buffer_sizes != NULL)
		free(cor->buffer_sizes);
	if (cor->buffer_codes != NULL)
		free(cor->buffer_codes);
}

void	write_exit_code2(int exit_code)
{
	if (exit_code == INVALID_CODE_SIZE)
		ft_putstr_fd("Invalid code size\n", 2);
	if (exit_code == FAIL_READ)
		ft_putstr_fd("Failed to read file\n", 2);
	if (exit_code == ERR_FILE)
		ft_putstr_fd("Invalid file with champion\n", 2);
	if (exit_code == ERR_CODE_INIT)
		ft_putstr_fd("Problems with initialize code size\n", 2);
	if (exit_code == ERR_STR_INIT)
		ft_putstr_fd("Problems with initialize string\n", 2);
	if (exit_code == INVALID_VISUAL)
		ft_putstr_fd("Incorrect flag_visual flag\n", 2);
	exit(0);
}

void	write_exit_code(int exit_code)
{
	if (exit_code == TOO_MANY_PLAYERS)
		ft_putstr_fd("Too many players\n", 2);
	if (exit_code == INVALID_FLAG_N)
		ft_putstr_fd("Incorrect use of the flag -n\n", 2);
	if (exit_code == DUPLICATE_NUM_N)
		ft_putstr_fd("Duplicate player number\n", 2);
	if (exit_code == INVALID_FLAG_D)
		ft_putstr_fd("Incorrect use of the flag dump\n", 2);
	if (exit_code == FEW_AC_DUMP)
		ft_putstr_fd("Too few argc for dump\n", 2);
	if (exit_code == FEW_AC_N)
		ft_putstr_fd("Too few argc for -n\n", 2);
	if (exit_code == FEW_AC_V)
		ft_putstr_fd("Too few argc for -v\n", 2);
	if (exit_code == INVALID_PARAM)
		ft_putstr_fd("Incorrect name file(use -h to see more)\n", 2);
	if (exit_code == FAIL_OPEN)
		ft_putstr_fd("Failed to open file\n", 2);
	if (exit_code == ERR_MAGIC)
		ft_putstr_fd("Invalid magic header\n", 2);
	if (exit_code == ERR_NO_NULL)
		ft_putstr_fd("No null control bytes\n", 2);
	exit(0);
}

void	exterminate(t_cor *cor, int exit_code)
{
	free_cor(cor);
	if (exit_code > 0 && exit_code < 12)
		write_exit_code(exit_code);
	else if (exit_code >= 12 && exit_code < 18)
		write_exit_code2(exit_code);
}

void	error_usage(void)
{
	ft_putstr_fd("Usage:\n \
	Example: ./corewar -dump 200 -visual 2 -aff -n -1 filename.cor\n \
	LOG: ./corewar -flag_visual [1;5] (1..2...) \n \
	1 - Exec operation 2 - Killed coursors filename.cor\n \
	3 - Main game params \n \
	Default Player Numbers: 1, 2, 3, 4...\n \
	Change Player Number: -n -1 filename.cor\n \
	Dump: ./corewar -dump 300 [Players](prints the memory after \
	300 cycles 32 bytes)\n \
	Dump: ./corewar -d 300 [Players](prints the memory after 300\
	cycles 64 bytes)\n \
	Game on! 👾 🤖 🔫 \n", 2);
	exit(1);
}
