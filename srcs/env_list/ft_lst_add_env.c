/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:37:49 by racohen           #+#    #+#             */
/*   Updated: 2020/02/10 13:52:32 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lst_add_env(t_list_env **alst, t_list_env *new)
{
	while (*alst)
		alst = &(*alst)->next;
	*alst = new;
}
