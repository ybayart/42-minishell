/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 23:59:52 by racohen           #+#    #+#             */
/*   Updated: 2020/02/16 17:57:32 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

typedef struct	s_gnl
{
	char			str[((BUFFER_SIZE > 0) ? BUFFER_SIZE + 1 : 1)];
	int				fd;
	int				i;
	int				len;
	int				l_line;
	int				tmp;
}				t_gnl;

int				get_next_line(int fd, char **line);

#endif
