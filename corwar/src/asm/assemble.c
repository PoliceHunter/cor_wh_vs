/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 11:21:41 by dcapers           #+#    #+#             */
/*   Updated: 2021/02/03 22:53:44 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "asm_op.h"
#include "asm_errors.h"
#include "fcntl.h"
#include "libft.h"

t_parser			*parser_init(int fd)
{
	t_parser		*parser;

	if (!(parser = (t_parser *)ft_memalloc(sizeof(t_parser))))
		kill_exe(ERR_PARSER_INIT);
	parser->fd = fd;
	parser->token = NULL;
	parser->last = NULL;
	parser->name = NULL;
	parser->comment = NULL;
	parser->code = NULL;
	parser->label = NULL;
	parser->row = 0;
	parser->op_pos = 0;
	parser->pos = 0;
	parser->code_size = 0;
	return (parser);
}

void				setup_mention_val(t_parser *p)
{
	t_label			*label;
	t_mention		*mention;
	int32_t			val;

	label = p->label;
	while (label)
	{
		mention = label->mention;
		while (mention)
		{
			val = mention->size == 2 ? (int16_t)(label->op_pos -
			mention->op_pos) : (int32_t)(label->op_pos - mention->op_pos);
			int32_to_bytecode(p->code, mention->pos, val, mention->size);
			mention = mention->next;
		}
		label = label->next;
	}
}

void				assemble(char *filename)
{
	int				fd;
	t_parser		*parser;
	t_token			*curr;

	if ((fd = open(filename, O_RDONLY)) == -1)
		kill_exe(ERR_FILE_OPEN);
	parser = parser_init(fd);
	parse_asm(parser);
	curr = parser->token;
	ft_putstr("setup_info\n");
	setup_info(parser, &curr);
	buildup_code(parser, curr);
	ft_putstr("BUILDED\n");
	setup_mention_val(parser);
	ft_putstr("MENTIONED\n");
	buildup_binary(parser, filename);
	free_asm(&parser);
}
