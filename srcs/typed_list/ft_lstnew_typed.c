/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_typed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:58:37 by racohen           #+#    #+#             */
/*   Updated: 2020/02/13 17:59:18 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_typed	*ft_lstnew_typed(char c)
{
	t_typed *elem;

	if ((elem = malloc(sizeof(t_typed))) == NULL)
		return (NULL);
	elem->c = c;
	elem->next = NULL;
	return (elem);
}
