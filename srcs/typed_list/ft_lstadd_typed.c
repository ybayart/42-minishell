/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_typed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:26:50 by racohen           #+#    #+#             */
/*   Updated: 2020/02/13 18:00:05 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lstadd_typed(t_typed **alst, t_typed *new)
{
	t_typed *tmp;

	tmp = *alst;
	*alst = new;
	new->next = tmp;
}
