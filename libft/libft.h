/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:11:29 by racohen           #+#    #+#             */
/*   Updated: 2020/02/14 13:57:35 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_putchar(char c);
int					ft_termputs(int c);
int					ft_atoi(const char *str);
void				ft_free_tab(void **ft_tab);
char				*ft_freeint(int *elem);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isspace(int c);
int					ft_isstrint(char *str);
char				*ft_itoa(int n);
void				*ft_memalloc(size_t size);
void				ft_putendl(char const *s);
void				ft_putstr(char const *str);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncpy(char *dst, char const *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(const char *str, char c);
char				**ft_strsplit(char const *s, char c);
char				**ft_splits(char const *s, char *set);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_third(char const *s1, char const *s2,
															const char *s3);
char				*ft_strfjoin(char *s1, char *s2);
char				*ft_strfrjoin(char *s1, char *s2, char *del);
char				*ft_strfdjoin(char *s1, char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
size_t				ft_tablen(const char **ft_tab);
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strnstr(const char *big, const char *little,
					size_t len);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strrchr(const char *s, int c);
size_t				ft_strnlastpos(const char *str, char c, int n);
char				*ft_strnew(size_t size);
int					ft_is_in(char *str, char c);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_substr(const char *s, unsigned int start, size_t len);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstadd_at(t_list **lst, t_list *new, int at);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
int					ft_lstcount(t_list *list);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel_at(t_list **list, int at);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
t_list				*ft_lstget_at(t_list *lst, int at);
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
											void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				ft_lst_sort(t_list **begin_list, int (*cmp)());
void				ft_lst_print(t_list *lst);
char				*ft_strreplace(char **str, char *search, char *replace);
void				ft_sort_string_tab(char **ft_tab);
char				**ft_strinsert(char **list, char *str, size_t pos);

#endif
