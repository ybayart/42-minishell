/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:50:47 by racohen           #+#    #+#             */
/*   Updated: 2019/11/08 08:34:27 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(const char *set, char c)
{
	if (*set == '\0' || c == '\0')
		return (1);
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(const char *s1, const char *set)
{
	int	start;
	int	len;

	start = 0;
	if (s1 == NULL)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	while (is_sep(set, s1[start]))
	{
		start++;
		if (s1[start] == '\0')
			return (ft_strdup(""));
	}
	len = ft_strlen(s1) - 1;
	while (is_sep(set, s1[len]) == 1)
		len--;
	return (ft_substr(s1, start, len - start + 1));
}
