/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 23:02:56 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/23 00:36:10 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
**	0: O_RDONLY
**	2: O_RDWR
**	10: O_RDWR | O_APPEND
**	514: O_RDWR | O_CREAT
**	522: O_RDWR | O_CREAT | O_APPEND
*/

#define MSGERROR "syntax error near unexpected token"

static char	istoken(char *token)
{
	if (token[0] == '\0' ||
		ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0 ||
		ft_strcmp(token, "|") == 0 || ft_strcmp(token, ";") == 0)
		return (1);
	return (0);
}

void		cutargs(char **ar)
{
	int		i;
	int		f_in;
	int		f_out;

	i = -1;
	f_in = 0;
	f_out = 1;
	while (ar[++i] != 0)
	{
		if (istoken(ar[i]) && istoken(ar[i + 1]) &&
		(ar[i][0] != '>' || ar[i + 1][0] != '>' || (istoken(ar[i + 2]) && i++)))
			return (print_error(5, MSGERROR, NULL, ar[i + 1]));
		if (ft_strcmp(ar[i], "<") == 0)
		{
			if ((f_in = open(ar[i + 1], 0)) == -1)
				return (print_error(3, ar[i + 1], NULL, NULL));
		}
		else if (ft_strcmp(ar[i], ">") == 0 && ar[i + 1] != 0 &&
				ft_strcmp(ar[i + 1], ">") == 0)
		{
			i++;
			if ((f_out = open(ar[i + 1], 522)) == -1)
				return (print_error(3, ar[i + 1], NULL, NULL));
		}
		else if (ft_strcmp(ar[i], ">") == 0)
		{
			if ((f_out = open(ar[i + 1], 514)) == -1)
				return (print_error(3, ar[i + 1], NULL, NULL));
		}
	}
}
