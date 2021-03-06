/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_print_typed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:10:45 by yanyan            #+#    #+#             */
/*   Updated: 2020/03/02 16:20:48 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lst_print_typed(t_typed *lst, int max)
{
	int		i;

	i = -1;
	while (lst != NULL)
	{
		i++;
		if (max != -1 && i >= max)
			break ;
		write(1, &(lst->c), 1);
		lst = lst->next;
	}
}
