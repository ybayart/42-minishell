/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:26:26 by racohen           #+#    #+#             */
/*   Updated: 2020/01/16 14:08:44 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "../libft/includes/libft.h"
# include "../srcs/env_list/list_env.h"
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/wait.h>
# ifndef PATH
#  define PATH "PATH"
# endif
# ifndef PWD
#  define PWD "PWD"
# endif
# ifndef HOME
#  define HOME "HOME"
# endif

typedef struct	s_mini
{
	t_list_env	*env;
	char		*out;
	char		*in;
	int			alive;
	int			last_exit;
}				t_mini;

t_mini *g_mini;

int				shell();
int				is_convert_red(char *str);
char			*search_bin(const char *path, const char *env_path);
int				ft_get_len(char **str);
int				check_builtins(char *tmp);
char			**replace_quote_path(char **cmd);
int				run_builtins(char *cmd, const char *bin, char **argv, char **env);
void			run_cmd(const char *bin, char **argv, char **env);
void			run_pwd(const char *bin, char **argv, char **env);
void			run_exit(const char *bin, char **argv, char **env);
void			run_env(const char *bin, char **argv, char **env);
void			run_unset(const char *bin, char **argv, char **env);
void			run_export(const char *bin, char **argv, char **env);
void			run_pwd(const char *bin, char **argv, char **env);
void			run_echo(const char *bin, char **argv, char **env);
void			run_cd(const char *bin, char **argv, char **env);
void			shell_ex(const char *bin, char **argv, char **env);

#endif
