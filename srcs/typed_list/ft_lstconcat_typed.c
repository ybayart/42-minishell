/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstconcat_typed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:48:16 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/18 14:47:30 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_lstconcat_typed(t_typed *lst)
{
	char	*str;
	int		i;

	if ((str = malloc(sizeof(char) * (ft_lstsize_typed(lst) + 1))) == NULL)
		return (NULL);
	i = 0;
	while (lst != NULL)
	{
		str[i++] = lst->c;
		lst = lst->next;
	}
	str[i] = '\0';
	return (str);
}
