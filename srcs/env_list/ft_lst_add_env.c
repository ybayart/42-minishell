/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:37:49 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 13:44:48 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_env.h"

void	ft_lst_add_env(t_list_env **alst, t_list_env *new)
{
	while (*alst)
		alst = &(*alst)->next;
	*alst = new;
}
