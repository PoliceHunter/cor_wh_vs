/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjohnsie <mjohnsie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:49:30 by dcapers           #+#    #+#             */
/*   Updated: 2021/01/29 19:51:44 by mjohnsie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_ERRORS_H

# define ASM_ERRORS_H

# define ERR_STR_INIT			"Initialize string"
# define ERR_TOKEN_INIT			"Initialize token"
# define ERR_PARSER_INIT		"Initialize parser"
# define ERR_LABEL_INIT			"Initializw label"
# define ERR_MENTION_INIT		"Initialize mention"
# define ERR_FILE_CREAT			"Can\'t creat file!"
# define ERR_FILE_OPEN			"Can\'t open file!"

# include "asm.h"

void				token_error(t_token *token);
void				label_error(t_token *token);
void				operator_error(t_token *token);
void				info_error(int error_code);
void				type_error(t_token *t, t_op *op, int arg_num);

#endif
