/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:21:44 by ksean             #+#    #+#             */
/*   Updated: 2020/11/06 23:22:59 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vector.h"

t_range		init_range(unsigned int start, unsigned int end)
{
	t_range range;

	range.start = start;
	range.end = end;
	return (range);
}

int			ret(int (*cmp)(void *, void *), t_vector *vec, t_range range,
			void *new_data)
{
	size_t pivot;

	pivot = ((range.end - range.start) / 2) + range.start;
	if ((*cmp)(get_from_vec(vec, pivot), new_data) == 0)
	{
		return (insert_with_sort_internal(vec, init_range(range.start,
				pivot), new_data, cmp));
	}
	if ((*cmp)(get_from_vec(vec, pivot), new_data) > 0)
	{
		return (insert_with_sort_internal(vec, init_range(range.start,
								pivot + 1), new_data, cmp));
	}
	else
	{
		return (insert_with_sort_internal(vec, init_range(pivot - 1,
								vec->size), new_data, cmp));
	}
}

int			insert_with_sort_internal(t_vector *vec, t_range range,
							void *new_data, int (*cmp)(void *, void *))
{
	void	*ptr;
	size_t	i;

	i = range.start;
	if (range.start == range.end)
	{
		push_back_vec(vec, new_data);
		return (vec->size - 1);
	}
	if (range.end - range.start <= 3)
	{
		while (i != range.end)
		{
			ptr = get_from_vec(vec, i);
			if ((*cmp)(ptr, new_data) > 0)
			{
				insert_into_vec(vec, i, new_data);
				return (i);
			}
			i++;
		}
		push_back_vec(vec, new_data);
		return (vec->size - 1);
	}
	return (ret(cmp, vec, init_range(range.start, range.end), new_data));
}

int			insert_with_sort(t_vector *vec, void *new_data,
						int (*cmp)(void *, void *))
{
	return (insert_with_sort_internal(vec,
					init_range(0, vec->size), new_data, cmp));
}

int			insert_into_vec(t_vector *vec, int index, void *element)
{
	unsigned int offset;

	if (index > vec->size)
		return (-1);
	if (index == 0)
	{
		push_front_vec(vec, element);
		return (0);
	}
	if (index == vec->size)
	{
		push_back_vec(vec, element);
		return (0);
	}
	if (vec->size >= vec->capacity)
		expand_vec(vec, vec->capacity * 2);
	offset = index * vec->elem_size;
	ft_memmove(vec->data + offset + vec->elem_size,
			vec->data + offset,
			vec->elem_size * (vec->size - index));
	ft_memcpy(vec->data + offset, element, vec->elem_size);
	++vec->size;
	return (0);
}
