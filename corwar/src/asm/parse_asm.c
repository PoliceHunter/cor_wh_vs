/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 09:01:32 by dcapers           #+#    #+#             */
/*   Updated: 2021/02/01 22:14:53 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "asm_errors.h"
#include "libft.h"

void			parse_command(t_parser *p, char *row, t_token *t)
{
	unsigned		start;

	start = p->col++;
	t->col = start;
	t->row = p->row;
	while (row[p->col] && ft_strchr(LABEL_CHARS, row[p->col]))
		p->col++;
	if ((p->col - start) && is_delimiter(row[p->col]))
	{
		t->content = get_content(p, row, start);
		add_token(p, t);
	}
	if (ft_strcmp(t->content, NAME_CMD_STRING) &&
			ft_strcmp(t->content, COMMENT_CMD_STRING))
		lexical_error(p->row, start);
}

void			parse_syms(t_parser *p, char *row, t_token *t)
{
	unsigned		start;

	t->col = p->col++;
	t->row = p->row;
	while (ft_strchr(LABEL_CHARS, row[p->col]) && !is_delimiter(row[p->col]))
		++p->col;
	t->content = get_content(p, row, t->col);
	if ((p->col - t->col) && row[p->col] == LABEL_CHAR && ++p->col)
		t->type = LABEL;
	else if ((p->col - t->col) && is_delimiter(row[p->col]))
	{
		if (t->type == INDIRECT)
			t->type = is_reg(t->content) ? REGISTER : OPERATOR;
	}
	else
		lexical_error(p->row, t->col);
	add_token(p, t);
}

void			parse_digits(t_parser *p, char *row, t_token *t)
{
	unsigned		col;

	t->col = p->col;
	t->row = p->row;
	if (row[p->col] == '-')
		p->col++;
	col = p->col;
	while (ft_isdigit(row[p->col]))
		p->col++;
	if ((p->col - col)
		&& (t->type == DIRECT || is_delimiter(row[p->col])))
	{
		t->content = get_content(p, row, t->col);
		add_token(p, t);
	}
	else if (t->type != DIRECT)
	{
		p->col = t->col;
		parse_syms(p, row, t);
	}
	else
		kill_exe(ERR_TOKEN_INIT);
}

void			parse_token(t_parser *p, char **row)
{
	if ((*row)[p->col] == COMMAND_CHAR)
		parse_command(p, *row, create_token(p, COMMAND));
	else if ((*row)[p->col] == SEPARATOR_CHAR && ++p->col)
		add_token(p, create_token(p, SEPARATOR));
	else if ((*row)[p->col] == '\n')
		add_token(p, create_token(p, NEW_LINE));
	else if ((*row)[p->col] == STR_CHR)
		parse_str(p, row, create_token(p, STRING));
	else if ((*row)[p->col] == DIRECT_CHAR && ++p->col)
	{
		if ((*row)[p->col] == LABEL_CHAR)
			parse_syms(p, *row, create_token(p, DIRECT_LABEL));
		else
			parse_digits(p, *row, create_token(p, DIRECT));
	}
	else if ((*row)[p->col] == LABEL_CHAR && ++p->col)
		parse_syms(p, *row, create_token(p, INDIRECT_LABEL));
	else
		parse_digits(p, *row, create_token(p, INDIRECT));
}

void			parse_asm(t_parser *parser)
{
	char		*row;

	row = NULL;
	while (get_row(parser, &row) > 0)
	{
		while (row && row[parser->col])
		{
			skip_spaces(parser, row);
			skip_comment(parser, row);
			if (row[parser->col])
				parse_token(parser, &row);
		}
		add_token(parser, create_token(parser, NEW_LINE));
		ft_strdel(&row);
	}
	add_token(parser, create_token(parser, END));
}
