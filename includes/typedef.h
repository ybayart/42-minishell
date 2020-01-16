/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:08:06 by ybayart           #+#    #+#             */
/*   Updated: 2020/01/16 15:17:39 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef struct	s_list_env
{
	char				*name;
	char				*value;
	struct s_list_env	*next;
}				t_list_env;

typedef struct	s_mini
{
	t_list_env	*env;
	char		*out;
	char		*in;
	int			alive;
	int			last_exit;
}				t_mini;

#endif
