/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:43:52 by racohen           #+#    #+#             */
/*   Updated: 2019/12/04 17:33:21 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_ENV_H
# define LIST_ENV_H

#include "../../libft/includes/libft.h"
#include <stdlib.h>

typedef struct			s_list_env
{
	char				*name;
	char				*value;
	struct s_list_env	*next;
}						t_list_env;

t_list_env				*ft_lst_new_env(char *name, char *value);
void					ft_lstdel_at_env(t_list_env **list, char *at);
char					*ft_lst_find_env(t_list_env **list, char *name);
void					ft_lst_add_env(t_list_env **alst, t_list_env *new);
void					ft_lst_clear_env(t_list_env **lst);
int						ft_lst_size_env(t_list_env *lst);
char					**ft_list_to_tab_env(t_list_env *list);

#endif
