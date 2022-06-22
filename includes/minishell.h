/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:38 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/21 22:00:53 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <time.h> 
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <ncurses.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <limits.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <term.h>

# define START_TOK 999
# define END_TOK 999
# define BUFFER_SIZE 1

# define NUL -1
# define LIMITERR -2

typedef enum e_token_type
{
	PIP,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	WORD,
	WSPACE,
	DOLLAR,
	INPUTE_REDI,
	OUTPUTE_REDI,
	INTPUTE_HEREDOC,
	OUTPUTE_HEREDOC,
}	t_token_type;

typedef struct s_list
{
	int				token;
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_point
{
	void			*content;
	struct s_point	*next;
}	t_point;

typedef struct s_env
{
	t_point			*point;
	pid_t			g_pid;
	char			*value;
	int				exit_status;
	int				index;
	int				index_env;
	char			*export_value;
	char			**env_new;
	int				sig;
	int				shlvl_val;
	int				status;
	struct s_env	*next;
}	t_env;

t_env	*g_glob;

typedef struct s_vars
{
	int		pth_i;
	int		pth_k;
	int		pth_a;
	int		pth_ans;
	char	*pth_str;
	char	*pth_str2;
	char	**pth_p;
	char	**pth_cmd;
	int		ck_j;
	int		ck_c;
	int		ck_n;
	int		ck_x;
	char	*ck_s;
	char	*ck_stri;
	int		c;
	int		c2;
	int		fd[2];
	int		fdd[2];
	int		z[2];
	char	*file_n;
	char	*value;
	int		st_in;
	int		st_out;
	t_list	*node;
	int		*id;
}	t_vars;

// ----- LISTS /////
t_list	*ft_lstnew(char *content, int tokn);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclearp(t_point **lst);
t_point	*ft_lstnewp(void *content);
t_point	*ft_lstlastp(t_point *lst);
void	ft_lstadd_backp(t_point **lst, t_point *new);
// ------- functions utils /////
int		skip_dquo(char *s, int i);
char	*ft_itoa(int n);
int		ft_strlen(char *s);
char	*ft_strdup(const char *src);
char	*ft_substr(char *s, int start, int len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	ft_free(char **str);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strtrim(char *s1, char *set);
char	*get_from_env(char **str, char *to_find);
int		ft_strlcpy(char *dest, char *src, int size);
char	*ft_strchrr(char *str, int c);
int		ft_skip_space(char *str, int i);
int		ft_error(char *str, int retu);
char	**ft_split_two(char *s, char c);
void	printf_list(t_list *lst);
char	*ft_strchr(const char *str, int pos);
char	*ft_strjoin_nf(char *s1, char *s2);
int		ft_is_last(t_list *node, int c, int c2, int end);
int		ft_strcmp_2(char *str1, char *str2);
//// ----- parsing ///
void	tokenizer(char *str, char **env);
int		check_tok(t_list *token, int tok);
int		ft_isalphaa(int c);
int		ft_isdigitt(int c);
int		check_str(char *str, int i);
int		check_tok(t_list *token, int tok);
int		check_tok_pip(t_list *token, int tok);
int		num_commande(char **str);
int		ft_execute_builtins(t_list *node, char **env);
////// ------ syntax ////
int		check_syntax(char *str);
int		check_syntax_list(t_list *list);
int		inside_limiters(char *str, char limiter, char c);
int		limiter_stat(char *str, char limiter);
int		check_tok(t_list *token, int tok);
int		ft_error_pipe(t_list *list);
////// --------- pipe ////
void	status_child(void);
void	printf_list_z(t_env *lst);
char	*get_shlvl(void);
void	incrument_shlvl(void);
int		ft_is_last(t_list *node, int c, int c2, int end);
void	ft_child_1(char *cmd, char **env, int *end_pipe, t_vars var);
void	ft_child_2(char *cmd, char **env, t_vars var);
void	ft_child_3(char *cmd, char **env, int *end_pipe, t_vars var);
char	*search_for_path(char **env);
void	ft_skip_node(t_list **node);
int		is2or1(int i);
int		ft_cheak(int i, char **cmd);
void	file_error(char *str);
int		process_2(char **argv, char **env, char *path, int fd[]);
int		process_1(char **argv, char **env, char *path, int fd[]);
char	*join(char *str1, char *str2, char *str3);
char	*unix_cmd(char	*line, char **argv);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	child_process(char *argv, char **env, t_list *node);
int		get_next_line_pipex(char **line);
void	here_doc(char *limiter, int argc);
char	*ft_strnstr(const char	*big, const char *little, size_t len);
char	*ft_strdup(const char *s1);
int		get_next_line(char **line);
int		check_tok_pip(t_list *token, int tok);
void	execute(char *argv, char **envp);
void	execute_tb(char *cmds, char **env, t_list *node, t_vars var);
int		forkpipe(int *end);
void	error(void);
int		open_file(char *argv, int i);
void	main_pipe(int num_com, char **str, char **env, t_list *node);
char	*get_path(char **envp);
char	*get_cmd(char *path, char **av, int i);
void	ft_freee(char **tabo, char *cmd);
char	*ft_path(char **env, char *cd);
void	ft_is_erreur(char **mycmd, char **mypath);
int		ft_checker1(t_list **node, char *str, int i, char **env);
int		ft_checker2(t_list **node, char *str, int i);
////------ builtins /////
void	ft_putstr_fd(char *s, int fd);
int		ft_check_n(char *str, char *substr);
int		ft_echo(char **args);
int		ft_isalnum(char *str);
int		ft_exit(char **str);
int		ft_atoi(const char *str);
void	ft_pwd(void);
t_env	*init_env(void *data);
t_env	*add_to_list(t_env *list, void *data);
t_env	*list_env(char **env);
void	test_builtins(t_list *node, char **env);
void	ft_env(char **str);
char	**new_env_function(t_env *list);
void	ft_export(char **env);
void	ft_cd(char **args);
char	*check_home_path(char **str);
t_env	*search_and_replce_oldpwd(t_env *list, void *data);
t_env	*search_and_replce_pwd(t_env *list, void *data);
int		check_for_equal(char *str);
void	sig_handler(int sig);
void	signal_handl(void);
void	ft_unset(char **str);
int		check_arg(char *arg);
void	deletenode_from_env(t_env *list, char *str, int len);
int		ft_isalnum1(int c);
int		ft_isalpha(int c);
void	ctrl_d(void);
void	status_child(void);
void	ft_putchar_fd(char c, int fd);
int		ft_cd_utils(char **args, int a);
char	*path_oldpwd(t_env *list);
void	ft_putstr_3(char *str, char *str1, char *str2);
char	*ft_cd_home(t_env *list, char **args);
void	print_sort_list(t_env *tmp1);
void	print_sort_list_utils(char *str);
void	check_test_builtins(char **cmd);
char	*ft_export_utils(char *str);
void	ft_export_utils1(char *str, t_env *tmp);
int		print_sort_list_utils1(int lr);
/////// i dont know
int		ft_execute_builtins(t_list *node, char **env);

#endif