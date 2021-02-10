/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_op.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjohnsie <mjohnsie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 09:06:01 by dcapers           #+#    #+#             */
/*   Updated: 2021/01/29 19:51:50 by mjohnsie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_OP_H
# define ASM_OP_H

# include "op.h"
# include "stdint.h"

typedef struct			s_op
{
	char				*name;
	uint8_t				code;
	uint8_t				args_num;
	char				types_code;
	uint8_t				types[3];
	uint8_t				dir_size;
}						t_op;

static t_op		g_op[16] = {
	{
		.name = "live",
		.code = 0x01,
		.args_num = 1,
		.types_code = 0,
		.types = {T_DIR, 0, 0},
		.dir_size = 4,
	},
	{
		.name = "ld",
		.code = 0x02,
		.args_num = 2,
		.types_code = 1,
		.types = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
	},
	{
		.name = "st",
		.code = 0x03,
		.args_num = 2,
		.types_code = 1,
		.types = {T_REG, T_REG | T_IND, 0},
		.dir_size = 4,
	},
	{
		.name = "add",
		.code = 0x04,
		.args_num = 3,
		.types_code = 1,
		.types = {T_REG, T_REG, T_REG},
		.dir_size = 4,
	},
	{
		.name = "sub",
		.code = 0x05,
		.args_num = 3,
		.types_code = 1,
		.types = {T_REG, T_REG, T_REG},
		.dir_size = 4,
	},
	{
		.name = "and",
		.code = 0x06,
		.args_num = 3,
		.types_code = 1,
		.types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
	},
	{
		.name = "or",
		.code = 0x07,
		.args_num = 3,
		.types_code = 1,
		.types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
	},
	{
		.name = "xor",
		.code = 0x08,
		.args_num = 3,
		.types_code = 1,
		.types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.dir_size = 4,
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.args_num = 1,
		.types_code = 0,
		.types = {T_DIR, 0, 0},
		.dir_size = 2,
	},
	{
		.name = "ldi",
		.code = 0x0A,
		.args_num = 3,
		.types_code = 1,
		.types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.dir_size = 2,
	},
	{
		.name = "sti",
		.code = 0x0B,
		.args_num = 3,
		.types_code = 1,
		.types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.dir_size = 2,
	},
	{
		.name = "fork",
		.code = 0x0C,
		.args_num = 1,
		.types_code = 0,
		.types = {T_DIR, 0, 0},
		.dir_size = 2,
	},
	{
		.name = "lld",
		.code = 0x0D,
		.args_num = 2,
		.types_code = 1,
		.types = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
	},
	{
		.name = "lldi",
		.code = 0x0E,
		.args_num = 3,
		.types_code = 1,
		.types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.dir_size = 2,
	},
	{
		.name = "lfork",
		.code = 0x0F,
		.args_num = 1,
		.types_code = 0,
		.types = {T_DIR, 0, 0},
		.dir_size = 2,
	},
	{
		.name = "aff",
		.code = 0x10,
		.args_num = 1,
		.types_code = 1,
		.types = {T_REG, 0, 0},
		.dir_size = 4,
	}
};

#endif
