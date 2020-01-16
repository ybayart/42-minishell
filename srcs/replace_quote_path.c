/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 11:24:29 by racohen           #+#    #+#             */
/*   Updated: 2019/12/04 17:41:16 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

char		*check_quote(char *input)
{
	char	first;
	char	*tmp;
	char	*temp;

	first = '\0';
	temp = input;
	tmp = ft_strdup("");
	while (*input)
	{
		if (first == '\0' && (*input == '\"' || *input == '\''))
			first = *input;
		else if ((*input != '\"' && *input != '\'') || *input != first)
			tmp = ft_strfjoin(tmp, ft_substr(input, 0, 1));
		input++;
	}
	free(temp);
	return (tmp);
}

char		*get_env(t_list_env **list, char *input)
{
	t_list_env	*cur;

	cur = *list;
	while (cur)
	{
		if (ft_strncmp(cur->name, input, ft_strlen(cur->name)) == 0)
		{
			return (ft_strfjoin(ft_strdup(cur->value),
				input + (ft_strlen(cur->name))));
		}
		cur = cur->next;
	}
	return (ft_strdup(""));
}

char	**replace_quote_path(char **cmd)
{
	int i;
	int	index;

	i = -1;
	while (cmd[++i])
	{
		cmd[i] = check_quote(cmd[i]);
		index = -1;
		while (cmd[i][++index])
		{
		/*	if (strncmp(&cmd[i][index], "$?", 2))
			{
				cmd[i] = ft_strfjoin(ft_substr(cmd[i], 0, index), ft_itoa(mini->last_exit));
				cmd[i] = ft_strfjoin(cmd[i], ft_substr(cmd[i],
					index + 1, ft_strlen(cmd[i])));
				index = -1; 
			}
			else */if (cmd[i][index] == '$')
			{
				cmd[i] = ft_strfjoin(ft_substr(cmd[i], 0, index),
					get_env(&mini->env, &cmd[i][index + 1]));
			}
		}
	}
	return (cmd);
}
