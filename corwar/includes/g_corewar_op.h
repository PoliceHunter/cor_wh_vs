/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_corewar_op.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:18:07 by tmyrcell          #+#    #+#             */
/*   Updated: 2021/02/10 11:18:09 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORWAR_G_COREWAR_OP_H
# define CORWAR_G_COREWAR_OP_H
# include "corwar.h"

static uint8_t			g_sizes[3] = {
	T_REG,
	T_DIR,
	IND_SIZE
};

static int	g_calc[3] = {
	192,
	48,
	12
};

static int	g_sdvig[3] = {
	6,
	4,
	2
};

static t_op		g_op[16] = {
	{
		.name = "live",
		.op_code = 0x01,
		.args_num = 1,
		.args_types_code = 0,
		.args_codes1 = {DIR_CODE, 0, 0},
		.args_codes2 = {DIR_CODE, 0, 0},
		.args_codes3 = {DIR_CODE, 0, 0},
		.modify_carry = 0,
		.dir_size = 4,
		.cycles = 10,
		.func = (void (*)(void *, void *)) &live
	},
	{
		.name = "ld",
		.op_code = 0x02,
		.args_num = 2,
		.args_types_code = 1,
		.args_codes1 = {DIR_CODE, REG_CODE, 0},
		.args_codes2 = {IND_CODE, REG_CODE, 0},
		.args_codes3 = {IND_CODE, REG_CODE, 0},
		.modify_carry = 1,
		.dir_size = 4,
		.cycles = 5,
		.func = (void (*)(void *, void *)) &ld
	},
	{
		.name = "st",
		.op_code = 0x03,
		.args_num = 2,
		.args_types_code = 1,
		.args_codes1 = {REG_CODE, REG_CODE, 0},
		.args_codes2 = {REG_CODE, IND_CODE, 0},
		.args_codes3 = {REG_CODE, IND_CODE, 0},
		.modify_carry = 0,
		.dir_size = 4,
		.cycles = 5,
		.func = (void (*)(void *, void *)) &st
	},
	{
		.name = "add",
		.op_code = 0x04,
		.args_num = 3,
		.args_types_code = 1,
		.args_codes1 = {REG_CODE, REG_CODE, REG_CODE},
		.args_codes2 = {REG_CODE, REG_CODE, REG_CODE},
		.args_codes3 = {REG_CODE, REG_CODE, REG_CODE},
		.modify_carry = 0,
		.dir_size = 4,
		.cycles = 10,
		.func = (void (*)(void *, void *)) &add
	},
	{
		.name = "sub",
		.op_code = 0x05,
		.args_num = 3,
		.args_types_code = 1,
		.args_codes1 = {REG_CODE, REG_CODE, REG_CODE},
		.args_codes2 = {REG_CODE, REG_CODE, REG_CODE},
		.args_codes3 = {REG_CODE, REG_CODE, REG_CODE},
		.modify_carry = 1,
		.dir_size = 4,
		.cycles = 10,
		.func = (void (*)(void *, void *)) &sub
	},
	{
		.name = "and",
		.op_code = 0x06,
		.args_num = 3,
		.args_types_code = 1,
		.args_codes1 = {REG_CODE, REG_CODE, REG_CODE},
		.args_codes2 = {DIR_CODE, DIR_CODE, REG_CODE},
		.args_codes3 = {IND_CODE, IND_CODE, REG_CODE},
		.modify_carry = 1,
		.dir_size = 4,
		.cycles = 6,
		.func = (void (*)(void *, void *)) &and
	},
	{
		.name = "or",
		.op_code = 0x07,
		.args_num = 3,
		.args_types_code = 1,
		.args_codes1 = {REG_CODE, REG_CODE, REG_CODE},
		.args_codes2 = {DIR_CODE, DIR_CODE, REG_CODE},
		.args_codes3 = {IND_CODE, IND_CODE, REG_CODE},
		.modify_carry = 1,
		.dir_size = 4,
		.cycles = 6,
		.func = (void (*)(void *, void *)) &or
	},
	{
		.name = "xor",
		.op_code = 0x08,
		.args_num = 3,
		.args_types_code = 1,
		.args_codes1 = {REG_CODE, REG_CODE, REG_CODE},
		.args_codes2 = {DIR_CODE, DIR_CODE, REG_CODE},
		.args_codes3 = {IND_CODE, IND_CODE, REG_CODE},
		.modify_carry = 1,
		.dir_size = 4,
		.cycles = 6,
		.func = (void (*)(void *, void *)) &xor
	},
	{
		.name = "zjmp",
		.op_code = 0x09,
		.args_num = 1,
		.args_types_code = 0,
		.args_codes1 = {DIR_CODE, 0, 0},
		.args_codes2 = {DIR_CODE, 0, 0},
		.args_codes3 = {DIR_CODE, 0, 0},
		.modify_carry = 0,
		.dir_size = 2,
		.cycles = 20,
		.func = (void (*)(void *, void *)) &zjmp
	},
	{
		.name = "ldi",
		.op_code = 0x0A,
		.args_num = 3,
		.args_types_code = 1,
		.args_codes1 = {REG_CODE, REG_CODE, REG_CODE},
		.args_codes2 = {DIR_CODE, DIR_CODE, REG_CODE},
		.args_codes3 = {IND_CODE, DIR_CODE, REG_CODE},
		.modify_carry = 0,
		.dir_size = 2,
		.cycles = 25,
		.func = (void (*)(void *, void *)) &ldi
	},
	{
		.name = "sti",
		.op_code = 0x0B,
		.args_num = 3,
		.args_types_code = 1,
		.args_codes1 = {REG_CODE, REG_CODE, REG_CODE},
		.args_codes2 = {REG_CODE, DIR_CODE, DIR_CODE},
		.args_codes3 = {REG_CODE, IND_CODE, DIR_CODE},
		.modify_carry = 0,
		.dir_size = 2,
		.cycles = 25,
		.func = (void (*)(void *, void *)) &sti
	},
	{
		.name = "fork",
		.op_code = 0x0C,
		.args_num = 1,
		.args_types_code = 0,
		.args_codes1 = {DIR_CODE, 0, 0},
		.args_codes2 = {DIR_CODE, 0, 0},
		.args_codes3 = {DIR_CODE, 0, 0},
		.modify_carry = 0,
		.dir_size = 2,
		.cycles = 800,
		.func = (void (*)(void *, void *)) &g_fork
	},
	{
		.name = "lld",
		.op_code = 0x0D,
		.args_num = 2,
		.args_types_code = 1,
		.args_codes1 = {DIR_CODE, REG_CODE, 0},
		.args_codes2 = {IND_CODE, REG_CODE, 0},
		.args_codes3 = {IND_CODE, REG_CODE, 0},
		.modify_carry = 1,
		.dir_size = 4,
		.cycles = 10,
		.func = (void (*)(void *, void *)) &lld
	},
	{
		.name = "lldi",
		.op_code = 0x0E,
		.args_num = 3,
		.args_types_code = 1,
		.args_codes1 = {REG_CODE, REG_CODE, REG_CODE},
		.args_codes2 = {DIR_CODE, DIR_CODE, REG_CODE},
		.args_codes3 = {IND_CODE, DIR_CODE, REG_CODE},
		.modify_carry = 1,
		.dir_size = 2,
		.cycles = 50,
		.func = (void (*)(void *, void *)) &lldi
	},
	{
		.name = "lfork",
		.op_code = 0x0F,
		.args_num = 1,
		.args_types_code = 0,
		.args_codes1 = {DIR_CODE, 0, 0},
		.args_codes2 = {DIR_CODE, 0, 0},
		.args_codes3 = {DIR_CODE, 0, 0},
		.modify_carry = 0,
		.dir_size = 2,
		.cycles = 1000,
		.func = (void (*)(void *, void *)) &lfork
	},
	{
		.name = "aff",
		.op_code = 0x10,
		.args_num = 1,
		.args_types_code = 1,
		.args_codes1 = {REG_CODE, 0, 0},
		.args_codes2 = {REG_CODE, 0, 0},
		.args_codes3 = {REG_CODE, 0, 0},
		.modify_carry = 0,
		.dir_size = 4,
		.cycles = 2,
		.func = (void (*)(void *, void *)) &aff
	}
};

#endif
