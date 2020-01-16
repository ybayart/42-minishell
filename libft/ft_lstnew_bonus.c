/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:58:37 by racohen           #+#    #+#             */
/*   Updated: 2019/11/04 21:30:19 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *elem;

	if ((elem = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
