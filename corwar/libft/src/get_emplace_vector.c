/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:19:35 by ksean             #+#    #+#             */
/*   Updated: 2020/11/06 23:21:09 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vector.h"

void		*get_last(t_vector *vec)
{
	if (vec->size == 0)
		return (NULL);
	return (get_from_vec(vec, vec->size - 1));
}

void		*get_first(t_vector *vec)
{
	if (vec->size == 0)
		return (NULL);
	return (get_from_vec(vec, 0));
}

const void	*get_from_vec_const(const t_vector *vec, int index)
{
	if (index >= vec->size)
		return (NULL);
	return (vec->data + (index * vec->elem_size));
}

void		emplace_back_vec(t_vector *vec, void *element)
{
	if (vec->size == vec->capacity)
		expand_vec(vec, vec->capacity * 2);
	ft_memmove(vec->data + (vec->size++ * vec->elem_size),
			element, vec->elem_size);
}

void		emplace_front_vec(t_vector *vec, void *element)
{
	if (vec->size == vec->capacity)
		expand_vec(vec, vec->capacity * 2);
	ft_memmove(vec->data + vec->elem_size, vec->data,
			vec->size++ * vec->elem_size);
	ft_memmove(vec->data, element, vec->elem_size);
}
