# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: racohen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 23:55:41 by racohen           #+#    #+#              #
#    Updated: 2020/03/01 16:36:56 by yanyan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

SAN = -fsanitize=address

NAME = minishell 

LIBFT_PATH = ./libft/

LIBFT_NAME = ft

COMPIL_LIB = -L$(LIBFT_PATH) -l$(LIBFT_NAME) -lncurses

SRCS_DIR = srcs/

INCS_DIR = includes/

SRCS_LIST = main.c \
			utils.c \
			shell.c \
			utils_shell.c \
			getargs_cmd.c \
			cutargs.c \
			utils_redir.c \
			search_bin.c \
			run_builtins.c \
			run_cmd.c \
			run_cd.c \
			run_pwd.c \
			run_exit.c \
			run_echo.c \
			run_unset.c \
			run_export.c \
			run_env.c \
			run_touch.c \
			replace_quote_path.c \
			print_error.c \
			wildcard.c \
			utils_wildcard.c \
			utils_wildcard_2.c \
			termcaps.c \
			utils_termcaps.c \
			history.c

SRCS_ENV =	ft_lst_add_env.c \
			ft_lst_clear_env.c \
			ft_lst_del_at_env.c \
			ft_lst_find_env.c \
			ft_lst_size_env.c \
			ft_lst_to_tab_env.c \
			ft_lst_new_env.c \
			ft_lst_replace_env.c

SRCS_TYPED=	ft_lstadd_typed.c \
			ft_lstadd_at_typed.c \
			ft_lstnew_typed.c \
			ft_lst_print_typed.c \
			ft_lstdel_at_typed.c \
			ft_lstsize_typed.c \
			ft_lstconcat_typed.c \
			ft_lst_clear_typed.c \
			ft_lst_push_str_typed.c \
			ft_lst_push_back_typed.c \
			ft_lst_get_at_typed.c

INCS=	define.h \
		ft_minishell.h \
		libinc.h \
		typedef.h

SRCS =  $(addprefix $(SRCS_DIR), $(SRCS_LIST)) \
		$(addprefix $(SRCS_DIR)env_list/, $(SRCS_ENV)) \
		$(addprefix $(SRCS_DIR)typed_list/, $(SRCS_TYPED)) \


OBJECT = $(patsubst %.c, %.o, $(SRCS))

HEADERS =	$(INCS_DIR)

all : $(NAME)

.c.o: 
	${CC} $(FLAGS) -c -I $(INCS_DIR) -I $(LIBFT_PATH) $< -o ${<:.c=.o}

$(NAME): $(OBJECT) libft $(addprefix $(INCS_DIR), $(INCS))
	$(CC) $(SAN) $(FLAGS) $(COMPIL_LIB) $(OBJECT) -o $(NAME)

libft: break_implicit_rule
	@make -C $(LIBFT_PATH)

break_implicit_rule:

clean:
	@rm -rf $(OBJECT)

fclean: clean
	@rm -rf $(NAME)

ffclean: fclean
	@cd $(LIBFT_PATH) && make fclean

re : fclean all

rre: ffclean all

.PHONY: re clean fclean 
