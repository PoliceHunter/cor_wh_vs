/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjohnsie <mjohnsie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 05:20:58 by dcapers           #+#    #+#             */
/*   Updated: 2021/01/29 20:01:41 by mjohnsie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "asm_errors.h"
#include "libft.h"

static void		setup_name(t_parser *p, t_token **token)
{
	*token = (*token)->next;
	if (!(p->name = ft_strsub((*token)->content, 0,
		ft_strlen((*token)->content))))
		kill_exe(ERR_STR_INIT);
	if (ft_strlen((*token)->content) > PROG_NAME_LENGTH)
		info_error(0);
	*token = (*token)->next;
}

static void		setup_comment(t_parser *p, t_token **token)
{
	*token = (*token)->next;
	if (!(p->comment = ft_strsub((*token)->content, 0,
		ft_strlen((*token)->content))))
		kill_exe(ERR_STR_INIT);
	if (ft_strlen((*token)->content) > COMMENT_LENGTH)
		info_error(1);
	*token = (*token)->next;
}

void			setup_info(t_parser *p, t_token **token)
{
	while (!p->name || !p->comment)
	{
		if ((*token)->type == COMMAND && !p->name &&
			!ft_strcmp((*token)->content, NAME_CMD_STRING))
			setup_name(p, token);
		else if ((*token)->type == COMMAND && !p->comment &&
			!ft_strcmp((*token)->content, COMMENT_CMD_STRING))
			setup_comment(p, token);
		if ((*token)->type != NEW_LINE)
			token_error(*token);
		*token = (*token)->next;
	}
}
