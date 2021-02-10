/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 11:21:41 by dcapers           #+#    #+#             */
/*   Updated: 2021/02/03 22:53:33 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

static void	free_tokens(t_token **list)
{
	t_token	*current;
	t_token	*delete;

	current = *list;
	while (current)
	{
		delete = current;
		current = current->next;
		ft_strdel(&(delete->content));
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}

static void	free_mentions(t_mention **list)
{
	t_mention	*current;
	t_mention	*delete;

	current = *list;
	while (current)
	{
		delete = current;
		current = current->next;
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}

static void	free_labels(t_label **list)
{
	t_label	*current;
	t_label	*delete;

	current = *list;
	while (current)
	{
		delete = current;
		current = current->next;
		ft_strdel(&(delete->name));
		free_mentions(&(delete->mention));
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}

void		free_asm(t_parser **parser)
{
	free_tokens(&((*parser)->token));
	ft_strdel(&((*parser)->name));
	ft_strdel(&((*parser)->comment));
	ft_strdel(&((*parser)->code));
	free_labels(&((*parser)->label));
	ft_memdel((void **)parser);
}

void		free_str(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
