/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjohnsie <mjohnsie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 12:36:17 by dcapers           #+#    #+#             */
/*   Updated: 2021/02/02 21:00:45 by mjohnsie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# define COMMAND_CHAR 		'.'
# define REG_CHAR     		'r'
# define STR_CHR      		'\"'
# define STATEMENT_LEN		14

# include <unistd.h>
# include <errno.h>
# include <stdint.h>
# include <stdlib.h>
# include "op.h"
# include "asm_op.h"

typedef struct s_parser			t_parser;
typedef struct s_token			t_token;
typedef struct s_label			t_label;
typedef struct s_mention		t_mention;

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	OPERATOR,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}	t_type;

struct					s_token
{
	char				*content;
	t_type				type;
	unsigned			row;
	unsigned			col;
	t_token				*next;
};

struct					s_label
{
	char				*name;
	int32_t				op_pos;
	t_mention			*mention;
	t_mention			*mention_last;
	t_label				*next;
};

struct					s_mention
{
	int32_t				pos;
	int32_t				op_pos;
	unsigned			row;
	unsigned			col;
	int32_t				size;
	t_mention			*next;
};

struct					s_parser
{
	int					fd;
	t_token				*token;
	t_token				*last;
	t_label				*label;
	t_label				*label_last;
	unsigned			row;
	unsigned			col;
	int32_t				op_pos;
	int32_t				pos;
	char				*name;
	char				*comment;
	char				*code;
	int32_t				code_size;

};

void					assemble(char *filename);
void					parse_asm(t_parser *parser);
void					parse_str(t_parser *p, char **row, t_token *t);
void					asm_test(char *s);
void					kill_exe(char *msg);
int						is_true_ext(const char *filename, const char *ext);
char					*change_ext(char *filename, const char *old,
						const char *ext);
void					skip_spaces(t_parser *p, char *row);
void					skip_comment(t_parser *p, char *row);
t_token					*create_token(t_parser *p, t_type type);
void					add_token(t_parser *p, t_token *token);
char					*get_content(t_parser *parser, const char *row,
						unsigned start);
int						is_delimiter(int c);
int						is_space(int c);
int						is_reg(const char *arg);
int						get_row(t_parser *parser, char **str);
void					setup_info(t_parser *p, t_token **token);
void					lexical_error(int row, int col);
t_op					*get_op(char *name);
void					int32_to_bytecode(char *data, int32_t pos,
							int32_t value, size_t size);
t_label					*create_label(char *name, int32_t pos);
t_mention				*create_mention(int32_t op_pos,
							int32_t pos, t_token *t, size_t size);
void					push_mention(t_label *label, t_mention *mention);
void					push_label(t_parser *p, t_label *label);
t_label					*find_label(t_label *label, char *name);
void					buildup_code(t_parser *p, t_token *curr);
void					buildup_binary(t_parser *p, char *filename);
void					resize_buff(t_parser *p);
int8_t					setup_arg(t_parser *p, t_op *op, t_token *curr,
						int8_t arg_num);
void					update_types_code(int8_t *types_code, int8_t type,
						int arg_num);
void					dump_tokens(t_token *t);
static void				free_tokens(t_token **list);
static void				free_labels(t_label **list);
static void				free_mentions(t_mention **list);
void					free_asm(t_parser **parser);
void					free_str(char **str);

#endif
