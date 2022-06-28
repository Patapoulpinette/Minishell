/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:18 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/28 09:45:23 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd_list
{
	char				*cmd;
	int					*redir_type;
	char				**redir_file;
	struct s_cmd_list	*next;
}	t_cmd_list;

typedef struct s_env_list
{
	char				*name;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_data
{
	char		*main_str;
	t_cmd_list	*cmd_table;
	t_env_list	*env_table;
	t_env_list	*env_table_sorted;
	int			squote;
	int			dquote;
	int			r_tabl;
	char		**paths;
	char		**arg_tabl;
	int			path_nbr;
	int			here_doc_nbr;
	int			lst_nbr;
	int			nbr;
	int			i;
	int			li;
	int			ly;
	int			j;
	int			rdj;
	int			x;
	int			exec_i;
	int			lexer_error;
	int			lexer_start;
	int			error_getcmd;
	int			main_error;
	int			**fds;
	int			pid;
	int			rdi;
	int			pskip;
	char		*pcommand;
	int			*redir_type;
	char		**redir_file;
	int			tabl_s;
	int			parser_error;
	int			rd_error;
	int			is_built_in;
	int			bin_nbr;
	int			bin_inpipe;
	int			nbr_save;
}	t_data;

//Lst - cmd ------------------------------------------
t_cmd_list	*ft_lstnew(char *cmd, int *redir_type, char **redir_file);
void		ft_lstadd_front(t_cmd_list **alst, t_cmd_list *new);
int			ft_lstsize(t_cmd_list *lst);
t_cmd_list	*ft_lstlast(t_cmd_list *lst);
void		ft_lstadd_back(t_cmd_list **alst, t_cmd_list *new);
void		ft_lstclear(t_cmd_list **lst);
//----------------------------------------------------

//Lst - env ------------------------------------------
t_env_list	*ft_env_lstnew(char *name, char *value);
void		ft_env_lstadd_front(t_env_list **alst, t_env_list *new);
int			ft_env_lstsize(t_env_list *lst);
t_env_list	*ft_env_lstlast(t_env_list *lst);
void		ft_env_lstadd_back(t_env_list **lst, t_env_list *new);
void		ft_env_lstclear(t_env_list **lst);
//----------------------------------------------------

//Parsing---------------------------------------------
int			ft_lexer(char *str, t_data *data); //parsing
int			ft_parser(char *str, t_data *data, int end); //parsing2
void		ft_addpipe(t_data *data);
void		quotes_switch(t_data *data, char *str, int i);
int			redir_parsing(char *str, t_data *data);
int			count_redir(char *str, t_data *data);
int			str_is_empty(char *str);
void		here_doc_fct(t_data *data, char *str);
int			ft_lexer2(t_data *data, char *str);
int			ft_parser2(t_data *data, char *str);
//----------------------------------------------------

//Environnement---------------------------------------
int			ft_env_var(t_data *data);
int			ft_put_env_in_lst(t_data *data, char **env);
void		ft_sort_list(t_data *data);
t_env_list	*ft_dup_list(t_env_list *list);
void		ft_insertion_sort(t_data *data);
int			ft_search_and_replace_env_var(t_data *data);
void		ft_replace_var_env(t_cmd_list *cmd_list, int pos, t_data *data);
char		*ft_is_var_env(t_data *data, char *cmd, int pos, int len);
//----------------------------------------------------

//Execution-------------------------------------------
int			ft_execution(t_data *data, char **env);
char		**recup_path(char **env, t_data *data);
char		*recupathline(char **env);
int			exec_one_cmd(t_data *data, char **env);
char		**get_cmd(t_data *data);
char		**put_cmd_in_arg(int i, t_data *data, char *str, char **tabl);
int			get_argnbr(char *str, t_data *data);
int			put_path(t_data *data);
int			cmd_redir(t_data *data, char **env, int nbr);
int			exec_cmds(t_data *data, char **env);
char		**rm_quote(char **tabl, t_data *data);
char		*rm_quote2(t_data *data, char **tabl, char *str);
int			forward_redir(t_data *data, int i);
int			backward_redir(t_data *data, int i, int nbr);
int			getcmd_and_pipe(t_data *data, char **env);
int			exec_cmds_second(t_data *data, char **env);
//----------------------------------------------------

//Builtins--------------------------------------------
int			built_in(t_data *data, char **env, int nbr);
int			ft_is_builtin(const char *s1);
void		bin_env(t_data *data);
int			bin_pwd();
void		bin_export(char **arg, t_data *data);
void		ft_display_env(t_env_list *list);
t_env_list	*ft_search_env(t_data *data, char *name);
void		bin_unset(char **arg, t_data *data);
t_env_list	*ft_search_preenv(t_data *data, char *name);
//----------------------------------------------------

//Errors----------------------------------------------
int			parserror(int nbr);
void		exekerror(int nbr);
//----------------------------------------------------

//Utils-----------------------------------------------
char		*ft_strmjoin(char *s1, char c);
size_t		ft_strlen(const char *str); // le mien navait pas le const;
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_isalnum(int c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(const char *s1);
char		*ft_replace_word(char *str, int start, int len, char *word);
int			ft_strncmp(const char *s1, const char *s2);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_1ststrjoin(char *s1, char *s2);
char		*ft_strjoin_c(char *s1, char c);
int			str_diff(char *str1, char *str2);
char		*ft_malloc_str(char *s1);
void		ft_putendl(char *s);
//----------------------------------------------------

#endif