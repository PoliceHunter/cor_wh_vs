/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:43:06 by ksean             #+#    #+#             */
/*   Updated: 2020/11/10 03:47:13 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <stdlib.h>
# include <string.h>
# include "libft.h"

typedef struct s_vector	t_vector;
struct					s_vector
{
	void				*data;
	int					size;
	int					capacity;
	size_t				elem_size;
};

typedef struct s_range	t_range;
struct					s_range
{
	unsigned int		start;
	unsigned			end;
};

t_vector				new_vector(size_t capacity, size_t elem_size);

void					free_vec(t_vector *vec);

void					expand_vec(t_vector *vec, size_t new_capacity);

/*
** Copy value from element to vec
*/
void					push_back_vec(t_vector *vec, void *element);

int						insert_with_sort(t_vector *vec, void *new_data,
						int (*cmp)(void *, void *));

/*
** Move value from element to vec
*/
void					emplace_back_vec(t_vector *vec, void *element);

void					*pop_back_vec(t_vector *vec);

void					push_front_vec(t_vector *vec, void *element);
void					emplace_front_vec(t_vector *vec, void *element);

void					*pop_front_vec(t_vector *vec);

void					*get_from_vec(t_vector *vec, int index);
void					*get_last(t_vector *vec);
void					*get_first(t_vector *vec);
const void				*get_from_vec_const(const t_vector *vec, int index);

int						insert_into_vec(t_vector *vec, int index,
						void *element);
int						remove_from_vec(t_vector *vec, int index);

void					swap_vec(t_vector *vec, int index1, int index2);

int						insert_with_sort_internal(t_vector *vec, t_range range,
						void *new_data, int (*cmp)(void *, void *));

#endif
