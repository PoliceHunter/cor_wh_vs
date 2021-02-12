/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corwar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:19:55 by tmyrcell          #+#    #+#             */
/*   Updated: 2021/02/10 11:19:56 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORWAR_CORWAR_H
# define CORWAR_CORWAR_H

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/vector.h"
# include "op.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdint.h>
# define TRUE 1
# define FALSE 0
# define FULL_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 4)
# define TOO_MANY_PLAYERS 1
# define INVALID_FLAG_N 2
# define DUPLICATE_NUM_N 3
# define INVALID_FLAG_D 4
# define FEW_AC_DUMP 5
# define FEW_AC_N 6
# define FEW_AC_V 7
# define INVALID_PARAM 8
# define FAIL_OPEN 9
# define ERR_MAGIC 10
# define ERR_NO_NULL 11
# define INVALID_CODE_SIZE 12
# define FAIL_READ 13
# define ERR_FILE 14
# define ERR_STR_INIT 15
# define ERR_CODE_INIT 16
# define INVALID_VISUAL 17
# define LIVE 2

typedef	struct s_cflag	t_cflag;
struct					s_cflag
{
	int					dump32;
	int					dump64;
	int					visual;
	int					aff;
};

typedef struct s_player	t_player;
struct					s_player
{
	char				*name;
	char				*comment;
	uint8_t				*code;
	int					id;
	int					index_player_ac;
	int					code_size;
	uint32_t			position_on_map;
	size_t				current_lives_num;
	size_t				previous_lives_num;
};

typedef struct			s_op
{
	char				*name;
	uint8_t				op_code;
	uint8_t				args_num;
	int					args_types_code;
	int					args_codes1[3];
	int					args_codes2[3];
	int					args_codes3[3];
	int					modify_carry;
	uint8_t				dir_size;
	int					cycles;
	void				(*func)(void *, void *);
}						t_op;

/*
** reg[REG_NUMBER];	- Array of variables for storing data
** carry;			- A special flag for operation of the "zjmp"
**					If it's 1, then the function updates the "position
** pos; 			- Map address
** op_code; 		- Contains the operation code
** cycle_to_exec; 	- number of cycles that remains to wait
** live_last_cycle; - Contain the cycle on which the last live op
** id; 				- index of process
*/

typedef struct			s_process
{
	int32_t				reg[REG_NUMBER];
	uint8_t				carry;
	uint32_t			pos;
	uint8_t				op_code;
	int					next_step;
	int					op_step;
	int					cycle_to_exec;
	int32_t				live_last_cycle;
	uint32_t			live_last_id;
	uint32_t			id;
	uint32_t			player_id;
	uint8_t				real_op_code;
}						t_process;

/*
** flag;					-Struct wich contain flags
** player[MAX_PLAYERS + 1]; -Struct witch contain info about player
** process;					-Struct vector contain processes
** cycle; 					-Counter total cycles begin start
** cycles_to_die; 			-The number of cycles between checks
** cycles_after_check;     	-Count cycles after check [0;cycles_to_die]
** count_players; 			-How many players in the game
** count_cursors; 			-Count cursors | On the start = count players
** count_lives; 			-Count live op on the cycle
** count_check; 			-Count checks [0;MAX_CHECKS]
** map[MEM_SIZE]; 			-Our map (stored battlefield)
** last_live_player; 		-The player who was last told that he was alive
*/

typedef	struct s_cor	t_cor;
struct					s_cor
{
	t_cflag				flag;
	t_player			player[MAX_PLAYERS + 1];
	t_vector			process;
	char				**files;
	uint32_t			cycle;
	int32_t				cycles_to_die;
	int32_t				cycles_after_check;
	int					count_players;
	int					count_cursors;
	int					count_lives;
	int					count_check;
	uint8_t				map[MEM_SIZE];
	int					last_live_player;
	int					*buffer_codes;
	int					*buffer_sizes;
	int32_t				*reg[REG_NUMBER + 1];
	uint8_t				*carry;
	struct s_vs			*vs;

};

/*
** dump_flags.c
*/

void					parse_dump_flag(t_cor *cor, char *num, int *i, int ac);
void					parse_d_flag(t_cor *cor, char *num, int *i, int ac);
int						check_flag(t_cor *cor);
void					check_dump_flag(t_cor *cor, char **av, int *i, int ac);

/*
** exit.c
*/

void					error_usage(void);
void					free_cor(t_cor *cor);
void					exterminate(t_cor *cor, int exit_code);

/*
** g_byte_int.c
*/

int32_t					byte_to_int32(t_cor *cor, t_process *process, int i,
						int size);
void					value32_to_map(t_cor *cor, int32_t val,
						uint32_t address, int size);
int32_t					byte_to_int32_2(t_cor *cor, uint32_t address, int size);

/*
** g_game_in_cycle.c
*/

void					game_in_cycle(t_cor *cor);

/*
** g_game_logic.c
*/

int						process_game_logic(t_cor *cor);
void					make_check(t_cor *cor);
void					parse_codetype(t_cor *cor, t_process *process);

/*
** g_get_put_values.c
*/

int32_t					get_address(t_process *process, int32_t step, int key);
int32_t					get_address_map(int32_t address, int32_t step);
int32_t					get_step(t_cor *cor, t_process *proc, int i);
int32_t					get_value(t_cor *cor, t_process *proc, int i);

/*
** g_help_buffer.c
*/

int						is_reg(t_cor *cor, t_process *process, int32_t step);
void					make_buffer_codes(t_cor *cor);
void					fill_buffer_with_zeros(t_cor *cor);

/*
** init.c
*/

void					init_cor(t_cor *cor, char **av);
void					init_arena(t_cor *cor);
t_process				*init_process(int32_t pos, t_vector process,
						int player_id);
void					init_processes(t_cor *cor);
void					init_players(t_cor *cor);

/*
** parse_champion.c
*/

int32_t					bytecode_to_int32(const uint8_t *bytecode, size_t size);
void					parse_champion_file(t_cor *cor);

/*
** parse_flags.c
*/

void					parse_flags(t_cor *cor, int ac, char **av);

/*
** player_num.c
*/

void					save_empty_num_player(t_cor *cor, const int *i);
void					save_num_player(t_cor *cor, char *num, int *i, int ac);
void					sort_players(t_cor *cor);
void					update_player_num(t_cor *cor);
void					dublicate_process(t_process *dubl, t_process *proc);

/*
** print.c
*/

void					print_log(t_cor *cor, t_process *process, int log_id);
void					print_arena(uint8_t *map, int print_mode);
void					print_arena(uint8_t *map, int print_mode);
void					print_intro(t_cor *cor);

/*
** operations
*/

void					add(t_cor *vm, t_process *proc);
void					sti(t_cor *vm, t_process *proc);
void					live(t_cor *vm, t_process *proc);
void					aff(t_cor *vm, t_process *proc);
void					and(t_cor *vm, t_process *proc);
void					g_fork(t_cor *vm, t_process *proc);
void					ld(t_cor *vm, t_process *proc);
void					ldi(t_cor *vm, t_process *proc);
void					lfork(t_cor *vm, t_process *proc);
void					lld(t_cor *vm, t_process *proc);
void					lldi(t_cor *vm, t_process *proc);
void					or(t_cor *vm, t_process *proc);
void					st(t_cor *vm, t_process *proc);
void					sub(t_cor *vm, t_process *proc);
void					xor(t_cor *vm, t_process *proc);
void					zjmp(t_cor *vm, t_process *proc);


int32_t		calc_addr(int32_t addr);
void		update_map(t_cor *vm, t_process *cursor, int32_t addr, int32_t size);

#endif
