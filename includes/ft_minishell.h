/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:26:26 by racohen           #+#    #+#             */
/*   Updated: 2020/02/28 17:20:31 by yanyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libinc.h"
# include "typedef.h"
# include "libft.h"
# include "define.h"

t_mini		*g_mini;

void		endofprog(void);
void		raw_mode(void);
void		init_mode(void);
void		sig_handler(int signo);
int			shell(void);
void		utils_shell(char **line);
void		utils_shell_do(char **line);
void		print_prompt(char clear);
void		print_term(char *cap, char prompt);
void		print_term_goto(char *cap, char prompt, int x, int y);
char		ft_termcaps(char c);
void		ft_termcaps_change_value(char c, int *state);
void		getargs_cmd(char *line);
char		*ft_addc(char *str, char c);
char		**ft_addstr(char **ft_tab);
void		cutargs(char **args);
char		istoken(char *token);
int			openfile(int *fd, char *file, int init, int mode);
void		make_redir(char state, int i, size_t len, int fd[2][2]);
void		setfd(int f_in, int f_out, char state);
void		space_cmd(char ***cmd, int f_in, int f_out);
void		utils_space_cmd(char ***cmd, size_t i, char *path);
int			is_convert_red(char *str);
char		*search_bin(char *path, const char *env_path);
int			ft_get_len(char **str);
int			check_builtins(char *tmp);
char		**replace_quote_path(char **cmd);
int			run_builtins(char *cmd, char **argv);
void		run_cmd(const char *bin, char **argv, char **env);
void		run_pwd();
void		run_exit(char **argv);
void		run_env();
void		run_unset(char **argv);
void		run_export(char **argv);
void		run_pwd();
void		run_echo(char **argv);
void		run_cd(char **argv);
void		run_touch(void);
void		check_empty_end(char ***args, size_t i);
char		wildcard(char ***args, int *pos, int initpos);
char		init_wildcard(t_list **sch, char ***args, int initpos,
													char *replace);
char		*w_getrootdir(char *str);
char		*w_getchilddir(char *str);
char		*w_getpattern(char *str);
char		test_wildcard(char str[], char pattern[], int n, int m);
char		list_dir(t_list **search, char *path[3]);
void		test_dir(struct dirent *dir, char *path[3], t_list **newlst,
																	int *i);
void		add_history(char *line);
char		get_history(void);
void		set_history(char c);

t_list_env	*ft_lst_new_env(char *name, char *value);
void		ft_lstdel_at_env(t_list_env **list, char *at);
char		*ft_lst_find_env(t_list_env **list, char *name);
void		ft_lst_add_env(t_list_env **alst, t_list_env *new);
void		ft_lst_clear_env(t_list_env **lst);
int			ft_lst_size_env(t_list_env *lst);
char		**ft_list_to_tab_env(t_list_env *list);
void		ft_lst_replace_env(t_list_env **list, char *name, char *value);
void		print_error(int state, char *str, char *bin, char *comp);

t_typed		*ft_lstnew_typed(char c);
void		ft_lstadd_typed(t_typed **alst, t_typed *new);
void		ft_lstadd_at_typed(t_typed **lst, t_typed *new, int at);
void		ft_lst_print_typed(t_typed *lst);
void		ft_lstdel_at_typed(t_typed **list, int at);
int			ft_lstsize_typed(t_typed *lst);
char		*ft_lstconcat_typed(t_typed *lst);
void		ft_lst_clear_typed(t_typed **lst);
void		ft_lst_push_str_typed(t_typed **lst, char *str);
void		ft_lst_push_back_typed(t_typed **lst, char c);
t_typed		*ft_lst_get_at_typed(t_typed *lst, int at);

#endif
