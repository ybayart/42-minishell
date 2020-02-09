/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 21:54:28 by racohen           #+#    #+#             */
/*   Updated: 2019/11/06 22:10:11 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*new;
	t_list	*prev;
	t_list	*curr;

	curr = lst;
	temp = NULL;
	while (curr != NULL)
	{
		if (f != NULL || curr->content != NULL)
			if ((curr->content = (*f)(curr->content)) == NULL)
				return (NULL);
		if ((new = ft_lstnew(curr->content)) == NULL)
			return (NULL);
		ft_lstadd_back(&temp, new);
		if (del != NULL)
			(*del)(curr->content);
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	return (temp);
}
