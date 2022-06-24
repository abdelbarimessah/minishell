/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:38 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/24 18:07:53 by amessah          ###   ########.fr       */
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
	char	*extb_path;
	char	**extb_cmd;
	int		extb_end_p[2];
	int		extb_a;
	int		extb_k;
	int		crt_pid;
	int		crt_wait_int;
	char	*crt_str;
	char	*crt_file_n;
	char	**crt_cmd;
	char	*crt_p;
	int		ct_i;
	int		ct_j;
	char	*ct_sb;
	char	*ct_s;
	char	*ct_st;
	char	*ct_limiter;
	char	**ct_env1;
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
	int		main_pi;
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
void	print_error_syntax(void);
int		check_syntax_list(t_list *list);
int		inside_limiters(char *str, char limiter, char c);
int		limiter_stat(char *str, char limiter);
int		check_tok(t_list *token, int tok);
int		ft_check_pipe(char *input);
int		ft_check_input_h(char *input);
int		ft_check_iredi(char *input);
int		ft_check_output_h(char *input);
int		ft_check_oredi(char *input);
////// --------- pipe ////
int		ft_create_tokens(struct s_list **node, char *str);
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
void	status_child(int wt);
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
void	ft_export_utils2(char *str);
int		ft_export_utils4(char **eq, char **eq1);
int		ft_export_utils5(char **eq, char **eq1);
int		ft_export_utils6(char **eq, char **eq1);
int		ft_export_utils7(t_env *tmp, char **eq1);
int		ft_export_utils8(t_env *tmp, char *str);
/////// extra functions for executions 
void	init_exec(t_vars *var);
int		inp_redi_exec(t_list **node, t_vars *var);
void	inp_herdc_exec(t_list **node, t_vars *var);
int		outp_redi_exec(t_list **node, t_vars *var);
int		outp_herdc_exec(t_list **node, t_vars *var);
int		out_herdc_redi_exec(t_list **node, t_vars *var);
void	loop_lst_exec(t_list **node, t_vars *var);
void	spc_null_word(t_list **node, t_vars *var);
void	ft_execute_comnd(t_list *node, char **env);
int		ft_execute_builtins(t_list *node, char **env);
int		outp_redi(t_list **nod, t_vars var);
int		outp_herdc(t_list **nod, t_vars var);
int		inp_redi(t_list **nod, t_vars var);
void	her_dc(t_list **nod, t_vars *var);
void	loop_list(t_list **nod, t_vars *var);
void	skip_outpherdc(t_list **head);
void	skip_outpredi(t_list **head);
char	*loop_join_pip(t_list **head, char *str);
void	ft_join_pipe(t_list *node, char **env);
void	dup_in(t_vars *var);
void	dup_out(t_vars *var);
void	error_jp(void);
int		check_order(t_list **node, t_vars *var);
void	execute_tb(char *cmds, char **env, t_list *node, t_vars var);
void	utils_ctrl_d(char *input_str);

///////////creations of tokens
int		spc_tok(char *str, t_list **node, t_vars *var);
int		dol_tok_utils(char *str, t_list **node, t_vars *var);
int		dol_tok(char *str, t_list **node, t_vars *var);
int		herdoc_dquo(char *str, t_vars *var);
int		herdoc_squo(char *str, t_vars *var);
void	init_vars(t_vars *var, char *str);
void	herdoc_utils(char *str, t_vars *var);
int		herdoc_utils_2(t_vars *var, char *str);
int		herdoc(t_vars *var, char *str, t_list **node);
int		check_sq_dq_p(t_vars *var, t_list **node, char *str);
int		check_inher_outher(t_vars *var, t_list **node, char *str);
void	last_tok(t_vars *var, char *str, t_list **node);
void	redi_in_out(t_vars *var, char *str, t_list **node);
int		token_cr_ut(t_vars *var, t_list **node, char *str);
int		token_cr(t_vars *var, t_list **node, char *str);
int		ft_create_tokens(struct s_list **node, char *str);

#endif