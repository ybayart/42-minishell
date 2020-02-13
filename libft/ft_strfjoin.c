/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:12:55 by racohen           #+#    #+#             */
/*   Updated: 2020/02/14 00:35:19 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfjoin(char *s1, char *s2)
{
	char *new_str;

	new_str = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (new_str);
}

char	*ft_strfdjoin(char *s1, char *s2)
{
	char *new_str;

	new_str = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (new_str);
}

char	*ft_strfrjoin(char *s1, char *s2, char *del)
{
	char *new_str;

	new_str = ft_strjoin(s1, s2);
	if (del)
		free(del);
	return (new_str);
}
