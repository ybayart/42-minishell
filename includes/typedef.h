/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:08:06 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/18 14:40:00 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "libft.h"

typedef struct	s_list_env
{
	char				*name;
	char				*value;
	struct s_list_env	*next;
}				t_list_env;

typedef struct	s_typed
{
	char			c;
	struct s_typed	*next;
}				t_typed;

typedef struct	s_mini
{
	t_list_env	*env;
	char		*out;
	char		*in;
	int			alive;
	int			last_exit;
	int			signal;
	int			redir;
	t_typed		*typed;
	int			typed_pos;
	int			prompt_size;
	char		ispipe;
	t_list		*history;
	int			history_pos;
	char		*current;
	char		exec;
}				t_mini;

typedef struct	s_cutargs
{
	int		i;
	int		j;
	int		f_in;
	int		f_out;
	int		fd[2][2];
	char	isredir;
	size_t	len;
	char	**cmd;
	char	state;
}				t_cutargs;

#endif
