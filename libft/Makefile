# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: racohen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 17:23:01 by racohen           #+#    #+#              #
#    Updated: 2020/02/14 13:58:01 by yanyan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRCS = ft_memset.c\
	   ft_bzero.c\
	   ft_memcpy.c\
	   ft_memccpy.c\
	   ft_memmove.c\
	   ft_memalloc.c\
	   ft_memchr.c\
	   ft_memcmp.c\
	   ft_strlen.c\
	   ft_isalpha.c\
	   ft_isdigit.c\
	   ft_isalnum.c\
	   ft_isascii.c\
	   ft_isprint.c\
	   ft_isstrint.c\
	   ft_toupper.c\
	   ft_tolower.c\
	   ft_strchr.c\
	   ft_strrchr.c\
	   ft_strncmp.c\
	   ft_strcmp.c\
	   ft_strlcpy.c\
	   ft_strncpy.c\
	   ft_strlcat.c\
	   ft_strnstr.c\
	   ft_strnlastpos.c\
	   ft_atoi.c\
	   ft_calloc.c\
	   ft_strdup.c\
	   ft_substr.c\
	   ft_strjoin.c\
	   ft_strjoin_third.c\
	   ft_strtrim.c\
	   ft_split.c\
	   ft_splits.c\
	   ft_itoa.c\
	   ft_strmapi.c\
	   ft_putchar_fd.c\
	   ft_termputs.c\
	   ft_putstr_fd.c\
	   ft_putendl_fd.c\
	   ft_putnbr_fd.c\
	   ft_sort_string_tab.c\
	   ft_strinsert.c\
		ft_lstadd.c \
		ft_lstadd_at.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstcount.c \
		ft_lstdel.c \
		ft_lstdel_at.c \
		ft_lstdelone.c \
		ft_lstget_at.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_lst_sort.c \
		ft_lst_print.c \
		ft_printf.c\
		ft_format_parser.c\
		write_c.c\
		write_d.c\
		write_p.c\
		write_pp.c\
		write_s.c\
		write_u.c\
		write_pr.c\
		write_x.c\
		ft_atoi_size.c\
		ft_freeall.c\
		ft_itoa_u.c\
		ft_setup_form.c\
		ft_strjoinfree.c\
		ft_strjoinfreeboth.c\
		ft_free_tab.c\
		ft_flags.c\
		get_next_line.c\
		ft_lstnew.c\
		ft_lstadd.c\
		ft_is_in.c\
		ft_isspace.c\
		ft_lstadd_at.c\
		ft_lstadd_back.c\
		ft_lstcount.c\
		ft_lstdel.c\
		ft_lstdel_at.c\
		ft_lstget_at.c\
		ft_putendl.c\
		ft_putstr.c\
		ft_strcat.c\
		ft_strcmp.c\
		ft_strfjoin.c\
		ft_strncat.c\
		ft_strndup.c\
		ft_strnew.c\
       	ft_strsplit.c\
		ft_strstr.c\
		ft_strreplace.c

OBJECT = $(SRCS:.c=.o)


all: $(NAME)

.c.o : 
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJECT) $(HEADERS)
	@ar rc $(NAME)  $(OBJECT)
	@ranlib $(NAME)

clean:
	@rm -rf $(OBJECT)

fclean: clean
	@rm -rf $(NAME)

re : fclean all

.PHONY: re clean fclean 
