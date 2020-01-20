/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 22:58:20 by racohen           #+#    #+#             */
/*   Updated: 2020/01/20 21:28:07 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_freeall(char *res, t_format *form, int crit)
{
	(void)crit;
	if (crit && res != NULL)
		free(res);
	if (crit && form != NULL)
		free(form);
	return (NULL);
}

char	*ft_freeint(int *elem)
{
	free(elem);
	return (NULL);
}
