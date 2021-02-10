/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjohnsie <mjohnsie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:21:44 by dcapers           #+#    #+#             */
/*   Updated: 2021/01/29 19:47:45 by mjohnsie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

int			is_space(int c)
{
	return (c == '\t' || c == '\v' ||
		c == '\f' || c == '\r' || c == ' ');
}

int			is_delimiter(int c)
{
	return (c == '\0' || c == '\n' || is_space(c)
		|| c == COMMAND_CHAR || c == STR_CHR
		|| c == DIRECT_CHAR || c == SEPARATOR_CHAR
		|| c == COMMENT_CHAR || c == ALT_COMMENT_CHAR);
}

void		skip_spaces(t_parser *p, char *row)
{
	if (!row || !*row)
		return ;
	while (is_space(row[p->col]))
		p->col++;
}

void		skip_comment(t_parser *p, char *row)
{
	if (!row || !*row)
		return ;
	if (row && (row[p->col] == COMMENT_CHAR || row[p->col] == ALT_COMMENT_CHAR))
		while (row[p->col] != '\0')
			p->col++;
}

void		lexical_error(int row, int col)
{
	ft_putstr_fd("Lexical error at [", 2);
	ft_putnbr_fd(row, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(col + 1, 2);
	ft_putstr_fd("]\n", 2);
	exit(1);
}
