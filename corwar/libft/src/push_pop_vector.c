/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:47:59 by ksean             #+#    #+#             */
/*   Updated: 2020/11/10 00:42:04 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vector.h"

void		*pop_back_vec(t_vector *vec)
{
	void			*result;
	unsigned int	offset;

	if (vec->size == 0)
		return (NULL);
	offset = --vec->size * vec->elem_size;
	result = malloc(vec->elem_size);
	ft_memmove(result, vec->data + offset, vec->elem_size);
	return (result);
}

void		push_front_vec(t_vector *vec, void *element)
{
	if (vec->size == vec->capacity)
		expand_vec(vec, vec->capacity * 2);
	ft_memmove(vec->data + vec->elem_size, vec->data,
	vec->size++ * vec->elem_size);
	ft_memcpy(vec->data, element, vec->elem_size);
}

void		*pop_front_vec(t_vector *vec)
{
	void *result;

	if (vec->size == 0)
		return (NULL);
	result = malloc(vec->elem_size);
	ft_memmove(result, vec->data, vec->elem_size);
	ft_memmove(vec->data, vec->data + vec->elem_size,
	--vec->size * vec->elem_size);
	return (result);
}

void		push_back_vec(t_vector *vec, void *element)
{
	unsigned int offset;

	if (vec->size == vec->capacity)
		expand_vec(vec, vec->capacity * 2);
	offset = vec->size++ * vec->elem_size;
	ft_memcpy(vec->data + offset, element, vec->elem_size);
}

void		swap_vec(t_vector *vec, int index1, int index2)
{
	void	*buf;
	int		offset1;
	int		offset2;

	if (index1 > vec->size || index2 > vec->size)
		return ;
	if (index1 == index2)
		return ;
	offset1 = vec->elem_size * index1;
	offset2 = vec->elem_size * index2;
	buf = malloc(vec->elem_size);
	ft_memcpy(buf, vec->data + offset1, vec->elem_size);
	ft_memmove(vec->data + offset1, vec->data + offset2, vec->elem_size);
	ft_memmove(vec->data + offset2, buf, vec->elem_size);
	free(buf);
}
