# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 20:28:46 by tmyrcell          #+#    #+#              #
#    Updated: 2021/02/08 23:00:56 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LIBFT =	ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strdup.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_atol.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_itoa.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstnew.c \
		ft_lstmap.c \
		ft_isupper.c \
		ft_islower.c \
		ft_isspace.c \
		ft_isxdigit.c \
		ft_isgraph.c \
		ft_strndup.c \
		get_next_line.c \
		ft_error.c \
		get_emplace_vector.c \
        init_free_vector.c \
        insert_sort_vector.c \
        push_pop_vector.c \
        ft_strjoin_by.c \
		ft_atoi32.c \
		is_filename.c \

        
FT_PRINTF = 		ad_0_after0x.c \
             		ad_0_aftersign.c \
             		ad_0_aftersps.c \
             		ad_fld_end.c \
             		ad_fld_strt.c \
            		analyze_format.c \
            		help_analyze_format.c \
            		count_af_dot.c \
            	 	find_format.c \
            	 	format_c.c \
            	  	format_d.c \
            	   	format_f.c \
            		format_o.c \
            		format_p.c \
            		format_s.c \
            		format_u.c \
            		format_x.c \
            	 	format_xx.c \
            	 	format_processing.c \
            		ft_big_itoa_base.c \
            	 	ft_dtoa.c \
            	 	ft_itoa_base.c \
            	  	ft_ldtoa.c \
            		ft_printf.c \
            	 	ft_strjoin_free.c \
            	  	ft_strjoin_free2.c \
            	  	ft_strrev.c  \
            	  	ft_strsub_free.c \
            		get_mods.c \
            	 	help_func_for_f.c \
            	  	inscrem_s.c \
            	   	locate_chr_index.c \
            	   	overlay_flags.c \
            		prec_ftoi.c  \
            	 	strlen.c  \
            	 	work_flags_with_d.c \
            		work_flags_with_f.c \
            	 	work_flags_with_o.c \
            	  	work_flags_with_p.c \
            	  	work_flags_with_s.c \
            		work_flags_with_u.c \
            		work_flags_with_x.c \
            	 	work_flags_with_per.c \
            		work_with_f.c \
            		ft_itoa_long.c \
            		ft_unsig_itoa_long.c \

RED			=	\033[0;31m
GREEN		=	\033[0;32m
NC			=	\033[0m

OBJSFD = objects

FT_PRINTF_SRCS = $(addprefix src/ft_printf/,$(FT_PRINTF))

LIBFT_SRCS = $(addprefix src/,$(LIBFT))

SRCS = $(LIBFT_SRCS) $(FT_PRINTF_SRCS)

OBJECTS = $(LIBFT:.c=.o) $(FT_PRINTF:.c=.o)

OBJS = $(addprefix $(OBJSFD)/, $(OBJECTS))

VPATH =	src:src/ft_printf

all: $(NAME) $(VECTOR)

$(NAME): $(OBJS)
	@echo "$(GREEN)...compiling binary libft...$(NC)"
	@/usr/bin/ar src $@ $(OBJS)
	@/usr/bin/ranlib $@
	@echo "$(GREEN)libft.a is created!$(NC)"

$(OBJSFD):
	@/bin/mkdir $@

$(OBJSFD)/%.o: %.c | $(OBJSFD)
	@/usr/bin/$(CC) $(CFLAGS) $(HDR) -c $< -o $@

HDR = -I./inc

clean:
	@/bin/rm -f $(OBJS)
	@/bin/rm -rf $(OBJSFD)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
