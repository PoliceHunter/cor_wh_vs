/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jczech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 10:35:15 by jczech            #+#    #+#             */
/*   Updated: 2019/11/12 11:35:39 by jczech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

char	*check_rest(char **rest, char **line, const int fd)
{
	char	*tmp;
	char	*work;

	work = NULL;
	if (rest[fd] && rest[fd][0])
	{
		work = ft_strchr(rest[fd], '\n');
		if (work)
			*work = '\0';
		*line = ft_strdup(rest[fd]);
		if (work && work[1])
		{
			tmp = rest[fd];
			rest[fd] = ft_strdup(++work);
			free(tmp);
		}
		else
			rest[fd][0] = '\0';
	}
	return (work);
}

int		get_next_line(const int fd, char **line)
{
	static char	*rest[256];
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	int			read_bytes;
	char		*work_rest;

	if (line == NULL || fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	*line = NULL;
	work_rest = check_rest(rest, line, fd);
	while (!work_rest && (read_bytes = read(fd, buf, BUFF_SIZE)))
	{
		buf[read_bytes] = '\0';
		if ((work_rest = ft_strchr(buf, '\n')))
		{
			*work_rest = '\0';
			work_rest++;
			free(rest[fd]);
			rest[fd] = ft_strdup(work_rest);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	return ((read_bytes || ft_strlen(rest[fd]) || *line) ? 1 : 0);
}
