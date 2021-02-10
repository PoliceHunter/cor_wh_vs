/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:13:01 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/29 16:25:01 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memmove_less_post(register char *dst, register
		const char *src, size_t length, register size_t t)
{
	t = length / WSIZE;
	while (t)
	{
		*(int *)dst = *(int *)src;
		src += WSIZE;
		dst += WSIZE;
		if (--t == 0)
			break ;
	}
	t = length & WMASK;
	while (t)
	{
		*--dst = *--src;
		if (--t == 0)
			break ;
	}
	return (dst);
}

void	*ft_memmove_less(register char *dst, register const
		char *src, size_t length, register size_t t)
{
	t = (int)src;
	if ((t | (int)dst) & WMASK)
	{
		if ((t ^ (int)dst) & WMASK || length < WSIZE)
			t = length;
		else
			t = WSIZE - (t & WMASK);
		length -= t;
		while (1)
		{
			if ((*dst++ = *src++) && --t == 0)
				break ;
		}
	}
	return (ft_memmove_less_post(dst, src, length, t));
}

void	*ft_memmove_greater_post(register char *dst, const register
		char *src, size_t length, register size_t t)
{
	t = length / WSIZE;
	while (t)
	{
		src -= WSIZE;
		dst -= WSIZE;
		*(int *)dst = *(int *)src;
		if (--t == 0)
			break ;
	}
	t = length & WMASK;
	while (t)
	{
		*--dst = *--src;
		if (--t == 0)
			break ;
	}
	return (dst);
}

void	*ft_memmove_greater(register char *dst, const
		register char *src, size_t length)
{
	register size_t t;

	src += length;
	dst += length;
	t = (int)src;
	if ((t | (int)dst) & WMASK)
	{
		if ((t ^ (int)dst) & WMASK || length <= WSIZE)
			t = length;
		else
			t &= WMASK;
		length -= t;
		while (t)
		{
			*--dst = *--src;
			if (--t == 0)
				break ;
		}
	}
	return (ft_memmove_greater_post(dst, src, length, t));
}

void	*ft_memmove(void *dst, const void *src, size_t length)
{
	register char			*dst1;
	register const char		*src1;
	register size_t			t;

	dst1 = dst;
	src1 = src;
	if (length == 0 || dst1 == src1)
		return (dst);
	if ((unsigned long)dst1 < (unsigned long)src1)
		return (ft_memmove_less(dst1, src1, length, t));
	return (ft_memmove_greater(dst1, src1, length));
}
