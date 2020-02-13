/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 11:24:29 by racohen           #+#    #+#             */
/*   Updated: 2020/02/10 14:06:55 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		get_size(char *str)
{
	int res;

	res = 0;
	while (*str != '\0' && *str != '$')
	{
		res++;
		str++;
	}
	return (res);
}

char	*get_env(t_list_env **list, char *input)
{
	t_list_env	*cur;

	cur = *list;
	if (ft_strcmp(cur->name, "?") == 0)
	{
		return (ft_strfjoin(ft_itoa(g_mini->last_exit),
			input + (ft_strlen(cur->name))));
	}
	while (cur)
	{
		if (ft_strncmp(cur->name, input, get_size(input)) == 0)
		{
			return (ft_strfjoin(ft_strdup(cur->value),
				input + (ft_strlen(cur->name))));
		}
		cur = cur->next;
	}
	return (ft_strjoin(ft_strdup(""), input + get_size(input)));
}

char	**replace_quote_path(char **cmd)
{
	int i;
	int	index;

	i = -1;
	while (cmd[++i])
	{
		index = -1;
		while (cmd[i][++index])
			if (cmd[i][index] == '$' && cmd[i][index + 1] != '\0')
			{
				cmd[i] = ft_strfjoin(ft_substr(cmd[i], 0, index),
					get_env(&g_mini->env, &cmd[i][index + 1]));
				i--;
			}
	}
	return (cmd);
}
