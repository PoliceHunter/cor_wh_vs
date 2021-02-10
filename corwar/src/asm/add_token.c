/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjohnsie <mjohnsie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 02:38:08 by dcapers           #+#    #+#             */
/*   Updated: 2021/01/29 19:55:32 by mjohnsie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_op.h"
#include "asm_errors.h"
#include "unistd.h"

t_token			*create_token(t_parser *p, t_type type)
{
	t_token			*token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		kill_exe(ERR_TOKEN_INIT);
	token->content = NULL;
	token->row = p->row;
	token->type = type;
	token->col = p->col;
	token->next = NULL;
	return (token);
}

void			add_token(t_parser *p, t_token *token)
{
	t_token		*tmp;

	if (!p || !token)
		return ;
	if (!p->token)
		p->token = token;
	if (p->last)
		p->last->next = token;
	p->last = token;
}

void			push_label(t_parser *p, t_label *label)
{
	if (p->label_last)
		p->label_last->next = label;
	p->label_last = label;
	if (!p->label)
		p->label = label;
}
