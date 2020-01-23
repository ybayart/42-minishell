/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:26:26 by racohen           #+#    #+#             */
/*   Updated: 2020/01/23 19:48:06 by ybayart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libinc.h"
# include "typedef.h"
# include "libft.h"
# include "define.h"

t_mini		*g_mini;

int			shell(void);
void		getargs_cmd(char *line);
char		*addchar(char *str, char c);
char		**addstr(char **tab);
void		cutargs(char **args);
char		istoken(char *token);
int			openfile(int *fd, char *file, int init, int mode);
void		make_redir(char state, int i, size_t len, int fd[2][2]);
void		space_cmd(char **cmd, int f_in, int f_out);
int			is_convert_red(char *str);
char		*search_bin(const char *path, const char *env_path);
int			ft_get_len(char **str);
int			check_builtins(char *tmp);
char		**replace_quote_path(char **cmd);
int			run_builtins(char *cmd, const char *bin, char **argv, char **env);
void		run_cmd(const char *bin, char **argv, char **env);
void		run_pwd(const char *bin, char **argv, char **env);
void		run_exit(const char *bin, char **argv, char **env);
void		run_env(const char *bin, char **argv, char **env);
void		run_unset(const char *bin, char **argv, char **env);
void		run_export(const char *bin, char **argv, char **env);
void		run_pwd(const char *bin, char **argv, char **env);
void		run_echo(const char *bin, char **argv, char **env);
void		run_cd(const char *bin, char **argv, char **env);
void		run_touch(void);
void		shell_ex(const char *bin, char **argv, char **env);

t_list_env	*ft_lst_new_env(char *name, char *value);
void		ft_lstdel_at_env(t_list_env **list, char *at);
char		*ft_lst_find_env(t_list_env **list, char *name);
void		ft_lst_add_env(t_list_env **alst, t_list_env *new);
void		ft_lst_clear_env(t_list_env **lst);
int			ft_lst_size_env(t_list_env *lst);
char		**ft_list_to_tab_env(t_list_env *list);
void		ft_lst_replace_env(t_list_env **list, char *name, char *value);
void		print_error(int state, char *str, char *bin, char *comp);

#endif
