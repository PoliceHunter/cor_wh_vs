/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 13:40:59 by dcapers           #+#    #+#             */
/*   Updated: 2021/02/03 22:59:51 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"
#include "op.h"
#include "libft.h"

t_label			*find_label(t_label *label, char *name)
{
	while (label)
	{
		if (!ft_strcmp(label->name, name))
			return (label);
		label = label->next;
	}
	return (label);
}

void			push_mention(t_label *label, t_mention *mention)
{
	if (label->mention_last)
		label->mention_last->next = mention;
	label->mention_last = mention;
	if (!label->mention)
		label->mention = mention;
}

t_mention		*create_mention(int32_t op_pos, int32_t pos,
			t_token *t, size_t size)
{
	t_mention	*mention;

	if (!(mention = (t_mention *)ft_memalloc(sizeof(t_mention))))
		kill_exe(ERR_MENTION_INIT);
	mention->pos = pos;
	mention->op_pos = op_pos;
	mention->row = t->row;
	mention->col = t->col;
	mention->size = size;
	mention->next = NULL;
	return (mention);
}

t_label			*create_label(char *name, int32_t pos)
{
	t_label		*label;

	if (!(label = (t_label *)ft_memalloc(sizeof(t_label))))
		kill_exe(ERR_LABEL_INIT);
	label->name = ft_strdup(name);
	label->mention = NULL;
	label->mention_last = NULL;
	label->op_pos = pos;
	label->next = NULL;
	return (label);
}
