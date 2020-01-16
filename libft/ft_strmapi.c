/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:35:24 by racohen           #+#    #+#             */
/*   Updated: 2019/11/06 18:05:13 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*fr;
	size_t	len;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if ((fr = malloc((len + 1) * sizeof(char))) == NULL)
		return (NULL);
	fr[len] = '\0';
	while (s[i] != '\0')
	{
		fr[i] = (*f)(i, s[i]);
		i++;
	}
	return (fr);
}
