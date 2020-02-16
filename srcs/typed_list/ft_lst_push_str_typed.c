/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_str_typed.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 00:40:44 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/16 04:17:36 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lst_push_str_typed(t_typed **lst, char *str)
{
	int			i;

	i = -1;
	while (str[++i] != '\0')
		ft_lst_push_back_typed(lst, str[i]);
}
