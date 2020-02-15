/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybayart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 21:43:18 by ybayart           #+#    #+#             */
/*   Updated: 2020/02/15 21:43:32 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <stdlib.h>

int		main(void)
{
	struct termios	raw;
	char			c;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ICANON);
	raw.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	while (read(0, &c, 1) == 1)
	{
		printf("%d\n", c);
	}
}
