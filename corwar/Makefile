# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/20 12:04:51 by dcapers           #+#    #+#              #
#    Updated: 2020/12/21 18:44:35 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM_NAME = asm
CORE_NAME = corewar

SRC_DIR = src/
OBJ_DIR = obj/

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

ASM_INCLUDES = -I$(INCLUDES) \
				-I$(INC_LIBFT)

CORE_INCLUDES = -I$(INCLUDES) \
				-I$(INC_LIBFT)

ASM_DIR = asm/
CORE_DIR = corewar/

ASM_LIST = asm_main.c \
			asm_utils.c \
			assemble.c \
			add_token.c \
			asm_errors.c \
			asm_utils2.c \
			parse_asm.c	\
			setup_info.c \
			setup_arg.c \
			create_label.c \
			resize_buff.c \
			buildup_code.c \
			buildup_binary.c \
			parse_str.c \
			free.c \

CORE_LIST = main.c \
            exit.c \
            g_add.c \
            g_aff.c \
            g_and.c \
            g_fork.c \
            g_game_in_cycle.c \
            g_game_logic.c \
            g_help_buffer.c \
            g_get_put_values.c \
            g_byte_int.c \
            g_ld.c \
            g_ldi.c \
            g_lfork.c \
            g_live.c \
           	g_lld.c \
            g_lldi.c \
            g_or.c \
            g_st.c \
            g_sti.c \
            g_sub.c \
            g_xor.c \
            g_zjmp.c \
            init.c \
            parse_flags.c \
            parse_champion.c \
            print.c \
            player_num.c \
            dump_flags.c \


COREWAR_VS_SOURCES_DIRECTORY = $(CORE_DIR)visual/
COREWAR_VS_SOURCES_LIST =\
    visual.c \

COREWAR_VS_SOURCES = $(addprefix $(COREWAR_VS_SOURCES_DIRECTORY), $(COREWAR_VS_SOURCES_LIST))

COREWAR_VS_OBJECTS_DIRECTORY = $(CORE_OBJ_DIR)visual/
COREWAR_VS_OBJECTS_LIST = $(patsubst %.c, %.o, $(COREWAR_VS_SOURCES_LIST))
COREWAR_VS_OBJECTS	= $(addprefix $(COREWAR_VS_OBJECTS_DIRECTORY), $(COREWAR_VS_OBJECTS_LIST))

ASM_SRC_DIR = $(SRC_DIR)$(ASM_DIR)
CORE_SRC_DIR = $(SRC_DIR)$(CORE_DIR)

ASM_OBJ_DIR = $(OBJ_DIR)$(ASM_DIR)
CORE_OBJ_DIR = $(OBJ_DIR)$(CORE_DIR)

ASM_OBJ_LIST = $(patsubst %.c, %.o, $(ASM_LIST))
CORE_OBJ_LIST = $(patsubst %.c, %.o, $(CORE_LIST))

ASM_OBJ = $(addprefix $(ASM_OBJ_DIR),  $(ASM_OBJ_LIST))
CORE_OBJ = $(addprefix $(CORE_OBJ_DIR),  $(CORE_OBJ_LIST))

ASM_SRC = $(addprefix $(ASM_SRC_DIR), $(ASM_LIST))
CORE_SRC = $(addprefix $(CORE_SRC_DIR), $(CORE_LIST))

LIBFT_ALL		= $(addsuffix .all,$(LIBFT_DIR))
LIBFT_CLEAN	= $(addsuffix .clean,$(LIBFT_DIR))
LIBFT_FCLEAN	= $(addsuffix .fclean,$(LIBFT_DIR))

INCLUDES		= includes/
INC_LIBFT	= $(addsuffix inc/,$(LIBFT_DIR))

ASM_HEADERS_LIST = asm.h errors.h
CORE_HEADERS_LIST = op.h corwar.h g_corewar_op.h visual.h

ASM_HEADERS = $(addprefix includes/, $(ASM_HEADERS_LIST))
CORE_HEADERS = $(addprefix includes/, $(CORE_HEADERS_LIST))

FLAGS = 

all: $(LIBFT_ALL) $(ASM_NAME) $(CORE_NAME)

clean: $(LIBFT_CLEAN)
	@rm -rf $(ASM_OBJ_DIR) $(CORE_OBJ_DIR) $(OBJ_DIR)

fclean: $(LIBFT_FCLEAN) clean
	@rm -rf $(ASM_NAME) $(CORE_NAME)

re:		fclean all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(ASM_OBJ_DIR):
	@mkdir -p $(ASM_OBJ_DIR)

$(CORE_OBJ_DIR):
	@mkdir -p $(CORE_OBJ_DIR)

$(COREWAR_VS_OBJECTS_DIRECTORY):
	@mkdir -p $(COREWAR_VS_OBJECTS_DIRECTORY)

$(ASM_NAME): $(LIBFT) $(OBJ_DIR) $(ASM_OBJ_DIR) $(ASM_OBJ)
	@gcc $(FLAGS) $(ASM_INCLUDES) $(ASM_OBJ) $(LIBFT) -o $(ASM_NAME)
	@echo "\033[32m$(ASM_NAME) binary created\033[0m."

$(CORE_NAME): $(LIBFT) $(OBJ_DIR) $(CORE_OBJ_DIR) $(CORE_OBJ) $(COREWAR_VS_OBJECTS_DIRECTORY) $(COREWAR_VS_OBJECTS)
	@gcc $(FLAGS) -lncurses $(CORE_INCLUDES) $(CORE_OBJ) $(LIBFT) $(COREWAR_VS_OBJECTS) -o $(CORE_NAME)
	@echo "\033[32m$(CORE_NAME) binary created\033[0m."

$(ASM_OBJ_DIR)%.o : $(ASM_SRC_DIR)%.c $(ASM_HEADERS)
	@echo "\033[34mASM COMPILING:\033[0m" $< 
	@gcc $(FLAGS) -o $@ -c $< $(ASM_INCLUDES)

$(CORE_OBJ_DIR)%.o : $(CORE_SRC_DIR)%.c $(CORE_HEADERS)
	@echo "\033[34mASM COMPILING:\033[0m" $< 
	@gcc $(FLAGS) -c $(CORE_INCLUDES) $< -o $@

%.all:
	@make -C $*

%.clean:
	@make -C $* clean

%.fclean:
	@make -C $* fclean

.PHONY: all clean fclean re