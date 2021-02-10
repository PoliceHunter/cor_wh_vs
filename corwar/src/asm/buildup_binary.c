/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildup_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 11:45:15 by dcapers           #+#    #+#             */
/*   Updated: 2021/02/01 22:22:22 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"
#include "fcntl.h"
#include "libft.h"

void			int32_to_bytecode(char *data, int32_t pos,
			int32_t value, size_t size)
{
	int8_t		i;

	i = 0;
	while (size)
	{
		data[pos + size - 1] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

int				is_true_ext(const char *filename, const char *ext)
{
	if (filename && ext && ft_strlen(filename) >= ft_strlen(ext))
		return (!ft_strcmp(ft_strchr(filename, '\0') - ft_strlen(ext), ext));
	else
		return (0);
}

char			*change_ext(char *filename, const char *old, const char *ext)
{
	char			*base;

	base = ft_strsub(filename, 0, ft_strlen(filename) - ft_strlen(old));
	if (!base)
		kill_exe(ERR_STR_INIT);
	if (!(filename = ft_strjoin(base, ext)))
		kill_exe(ERR_STR_INIT);
	ft_strdel(&base);
	return (filename);
}

void			write_bytecode(t_parser *p, int fd)
{
	char			*bytecode;
	int32_t			leng;
	int32_t			pos;

	leng = 4 + PROG_NAME_LENGTH + 8 + COMMENT_LENGTH + 4 + p->pos;
	if (!(bytecode = ft_strnew(leng)))
		kill_exe(ERR_STR_INIT);
	pos = 0;
	int32_to_bytecode(bytecode, pos, COREWAR_EXEC_MAGIC, 4);
	pos += 4;
	ft_memcpy(&bytecode[pos], p->name, ft_strlen(p->name));
	pos += PROG_NAME_LENGTH + 4;
	int32_to_bytecode(bytecode, pos, p->pos, 4);
	pos += 4;
	ft_memcpy(bytecode + pos, p->comment, ft_strlen(p->comment));
	pos += COMMENT_LENGTH + 4;
	ft_memcpy(&bytecode[pos], p->code, p->pos);
	write(fd, bytecode, (size_t)leng);
	free(bytecode);
}

void			buildup_binary(t_parser *p, char *filename)
{
	int		fd;

	filename = change_ext(filename, ".s", ".cor");
	if ((fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		kill_exe(ERR_FILE_CREAT);
	write_bytecode(p, fd);
	ft_putstr("Writing output program to ");
	ft_putstr(filename);
	ft_putchar('\n');
	free(filename);
}
