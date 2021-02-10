/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:46:34 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/06 19:18:13 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static int	recording_process(const char *input, va_list ap, char **result)
{
	const char		*ptr;
	char			*output;
	unsigned int	offset;
	unsigned int	mod_size;
	int				local_size;

	offset = 0;
	while ((ptr = ft_strchr(input, '%')))
	{
		*result = ft_str_concat_unsafe(*result, input, offset, ptr - input);
		offset += (ptr - input);
		local_size = ft_find_format(&ptr, &output, ap, &mod_size);
		if (local_size == -1)
		{
			ft_strdel(result);
			return (ft_strlen(input));
		}
		*result = ft_str_concat_unsafe(*result, output, offset, local_size);
		offset += local_size;
		ft_strdel(&output);
		input = ptr + mod_size;
	}
	local_size = ft_strlen(input);
	*result = ft_str_concat_unsafe(*result, input, offset, local_size);
	return ((int)(offset + local_size));
}

int			ft_printf(const char *format, ...)
{
	char	*ret;
	va_list	ap;
	size_t	len;

	ret = NULL;
	va_start(ap, format);
	len = recording_process(format, ap, &ret);
	if (ret)
	{
		write(1, ret, len);
		free(ret);
	}
	va_end(ap);
	return (len);
}

static char	*ft_strncpy_unsafe(char *dst, const char *src, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char		*ft_str_concat_unsafe(char *left, const char *right, size_t offset,
		size_t count)
{
	char *result;

	result = ft_strnew(offset + count);
	if (!result)
		return (NULL);
	if (left)
	{
		ft_strncpy_unsafe(result, left, offset);
		free(left);
	}
	ft_strncpy_unsafe(result + offset, right, count);
	return (result);
}
