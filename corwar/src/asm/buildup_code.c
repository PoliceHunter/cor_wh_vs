/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildup_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 11:43:34 by dcapers           #+#    #+#             */
/*   Updated: 2021/02/01 21:12:51 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"

void			setup_label(t_parser *p, t_token *t)
{
	t_label			*label;

	if (!(label = find_label(p->label, t->content)))
		push_label(p, create_label(t->content, p->op_pos));
	if (label && label->op_pos == -1)
	{
		label->op_pos = p->pos;
	}
}

int8_t			setup_args(t_parser *p, t_token **curr, t_op *op)
{
	int8_t			arg_num;
	int8_t			types_code;
	int8_t			type;

	types_code = 0;
	arg_num = 0;
	while (arg_num < op->args_num)
	{
		if ((*curr)->type >= REGISTER && (*curr)->type <= INDIRECT_LABEL)
		{
			update_types_code(&types_code,
				setup_arg(p, op, *curr, arg_num), arg_num);
			(*curr) = (*curr)->next;
		}
		else
			token_error(*curr);
		if (arg_num++ != op->args_num - 1)
		{
			if ((*curr)->type != SEPARATOR)
				token_error((*curr));
			(*curr) = (*curr)->next;
		}
	}
	return (types_code);
}

void			setup_operator(t_parser *p, t_token **curr)
{
	int8_t		types_code;
	t_op		*op;

	if ((op = get_op((*curr)->content)))
	{
		p->code[p->pos++] = op->code;
		(*curr) = (*curr)->next;
		if (op->types_code)
			p->pos++;
		types_code = setup_args(p, curr, op);
		if (op->types_code)
			p->code[p->op_pos + 1] = types_code;
	}
	else
		operator_error(*curr);
}

void			buildup_code(t_parser *p, t_token *curr)
{
	while (curr->type != END)
	{
		if (p->pos >= p->code_size)
			resize_buff(p);
		p->op_pos = p->pos;
		if (curr->type == LABEL)
		{
			setup_label(p, curr);
			curr = curr->next;
		}
		if (curr->type == OPERATOR)
			setup_operator(p, &curr);
		if (curr->type != NEW_LINE)
			token_error(curr);
		else
			curr = curr->next;
	}
}
