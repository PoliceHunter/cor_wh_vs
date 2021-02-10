/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjohnsie <mjohnsie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:18:31 by ksean             #+#    #+#             */
/*   Updated: 2021/01/29 20:15:24 by mjohnsie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vector.h"

void		*get_from_vec(t_vector *vec, int index)
{
	if (index >= vec->size)
		return (NULL);
	return (vec->data + (index * vec->elem_size));
}

t_vector	new_vector(size_t capacity, size_t elem_size)
{
	t_vector res;

	res.size = 0;
	res.capacity = capacity;
	res.elem_size = elem_size;
	res.data = malloc(res.capacity * res.elem_size);
	return (res);
}

void		free_vec(t_vector *vec)
{
	free(vec->data);
	vec->data = NULL;
	vec->capacity = 0;
	vec->size = 0;
}

int			remove_from_vec(t_vector *vec, int index)
{
	if (index > vec->size)
		return (-1);
	if (vec->size == 0)
		return (-1);
	ft_memmove(vec->data + (vec->elem_size * index),
			vec->data + (vec->elem_size * (index + 1)),
			vec->elem_size * (vec->size - index));
	vec->size--;
	return (0);
}

void		expand_vec(t_vector *vec, size_t new_capacity)
{
	void *new_data;

	vec->capacity = new_capacity;
	new_data = malloc(vec->capacity * vec->elem_size);
	if (new_data == NULL)
	{
		ft_printf("MALLOC_PANIC");
		exit(1);
	}
	ft_memmove(new_data, vec->data, vec->size * vec->elem_size);
	free(vec->data);
	vec->data = new_data;
}
