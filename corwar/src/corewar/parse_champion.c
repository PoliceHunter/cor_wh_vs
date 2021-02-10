/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:13:40 by tmyrcell          #+#    #+#             */
/*   Updated: 2021/02/09 12:13:42 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"

int32_t			bytecode_to_int32(const uint8_t *bytecode, size_t size)
{
	int32_t	result;
	_Bool	sign;
	int		i;

	result = 0;
	sign = (_Bool)(bytecode[0] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((bytecode[size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += bytecode[size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

static int32_t	parse_int32(t_cor *cor, int fd)
{
	ssize_t	size;
	uint8_t	buffer[4];

	size = read(fd, &buffer, 4);
	if (size == -1)
		exterminate(cor, FAIL_READ);
	if (size < 4)
		exterminate(cor, ERR_FILE);
	return (bytecode_to_int32(buffer, 4));
}

static char		*parse_str(t_cor *cor, int fd, size_t len)
{
	ssize_t	size;
	char	*buffer;

	if (!(buffer = ft_strnew(len)))
		exterminate(cor, ERR_STR_INIT);
	size = read(fd, buffer, len);
	if (size == -1)
		exterminate(cor, FAIL_READ);
	if (size < (ssize_t)len)
		exterminate(cor, ERR_FILE);
	return (buffer);
}

static uint8_t	*parse_code(t_cor *cor, int fd, size_t len)
{
	long int	size;
	uint8_t		*buffer;
	uint8_t		byte;

	if (!(buffer = malloc(len)))
		exterminate(cor, ERR_CODE_INIT);
	size = read(fd, buffer, len);
	if (size == -1)
		exterminate(cor, FAIL_READ);
	if (size < (ssize_t)len || read(fd, &byte, 1) != 0)
		exterminate(cor, ERR_FILE);
	return (buffer);
}

void			parse_champion_file(t_cor *cor)
{
	int i;
	int fd;

	i = -1;
	while (++i < cor->count_players)
	{
		if (ft_strlen(cor->files[cor->player[i].index_player_ac]) <= 4)
			exterminate(cor, INVALID_PARAM);
		if ((fd = open(cor->files[cor->player[i].index_player_ac],
				O_RDONLY)) < 0)
			exterminate(cor, FAIL_OPEN);
		if (parse_int32(cor, fd) != COREWAR_EXEC_MAGIC)
			exterminate(cor, ERR_MAGIC);
		cor->player[i].name = parse_str(cor, fd, PROG_NAME_LENGTH);
		if (parse_int32(cor, fd) != 0)
			exterminate(cor, ERR_NO_NULL);
		if ((cor->player[i].code_size = parse_int32(cor, fd)) < 0 ||
			cor->player[i].code_size > CHAMP_MAX_SIZE)
			exterminate(cor, INVALID_CODE_SIZE);
		cor->player[i].comment = parse_str(cor, fd, COMMENT_LENGTH);
		if (parse_int32(cor, fd) != 0)
			exterminate(cor, ERR_NO_NULL);
		cor->player[i].code = parse_code(cor, fd, cor->player[i].code_size);
		close(fd);
	}
}
