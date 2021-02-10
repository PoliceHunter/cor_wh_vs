/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 11:58:47 by dcapers           #+#    #+#             */
/*   Updated: 2021/02/03 22:56:15 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_errors.h"
#include "libft.h"
#include "unistd.h"
#include "op.h"
#include "asm.h"

void			kill_exe(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putchar('\n');
	exit(0);
}

int				is_reg(const char *arg)
{
	int	i;

	i = 0;
	if (ft_strlen(arg) >= 2 && ft_strlen(arg) <= 3 && arg[i] == REG_CHAR)
	{
		i++;
		while (ft_isdigit(arg[i]))
			i++;
		return (!arg[i] && ft_atoi(&arg[1]) > 0);
	}
	return (0);
}

char			*get_content(t_parser *parser, const char *row, unsigned start)
{
	char	*content;
	int		len;

	if (row[start] == LABEL_CHAR)
		start++;
	len = parser->col - start;
	if (!(content = ft_strsub(row, start, len)))
		kill_exe(ERR_STR_INIT);
	return (content);
}

int				get_row(t_parser *p, char **str)
{
	int			size;

	if ((size = get_next_line(p->fd, str)) == -1)
		kill_exe(ERR_FILE_OPEN);
	p->row++;
	p->col = 0;
	return (size);
}
