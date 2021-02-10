/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 01:48:45 by dcapers           #+#    #+#             */
/*   Updated: 2021/02/08 23:05:19 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "asm_op.h"
#include "asm_errors.h"
#include "libft.h"

static int8_t	get_arg_type(t_type type)
{
	if (type == DIRECT || type == DIRECT_LABEL)
		return (T_DIR);
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return (T_IND);
	else if (type == REGISTER)
		return (T_REG);
	else
		return (0);
}

void			setup_register(t_parser *p, t_token *curr, t_op *op)
{
	int32_to_bytecode(p->code, p->pos,
		(int8_t)ft_atoi(&curr->content[1]), 1);
	p->pos++;
}

void			setup_num(t_parser *p, t_token *curr, t_op *op)
{
	size_t		size;
	int32_t		val;

	size = curr->type == INDIRECT ? IND_SIZE : op->dir_size;
	val = size == 2 ? (int16_t)ft_atoi32(curr->content) :
						(int32_t)ft_atoi32(curr->content);
	int32_to_bytecode(p->code, p->pos, val, size);
	p->pos += size;
}

void			setup_mention(t_parser *p, t_token *curr, t_op *op)
{
	size_t			size;
	t_label			*label;

	size = curr->type == INDIRECT_LABEL ? IND_SIZE : op->dir_size;
	if (!(label = find_label(p->label, curr->content)))
	{
		label = create_label(curr->content, -1);
		push_label(p, label);
	}
	push_mention(label, create_mention(p->op_pos, p->pos, curr, size));
	p->pos += size;
}

int8_t			setup_arg(t_parser *p, t_op *op, t_token *curr, int8_t arg_num)
{
	int8_t		type;

	type = get_arg_type(curr->type);
	if (!(op->types[arg_num] & type))
		type_error(curr, op, arg_num);
	if (curr->type == INDIRECT || curr->type == DIRECT)
		setup_num(p, curr, op);
	else if (curr->type == INDIRECT_LABEL ||
		curr->type == DIRECT_LABEL)
		setup_mention(p, curr, op);
	else
		setup_register(p, curr, op);
	return (type);
}
