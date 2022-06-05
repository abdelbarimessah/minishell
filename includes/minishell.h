/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:38 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/05 13:25:59 by ntanjaou         ###   ########.fr       */
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

# define START_TOK 999
# define END_TOK 999
# define BUFFER_SIZE 1

typedef enum e_token_type
{
	PIP,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	WORD,
	SPACE,
	DOLLAR,
	INPUTE_REDI,
	OUTPUTE_REDI,
    INTPUTE_HEREDOC,
    OUTPUTE_HEREDOC,
} t_token_type;

typedef struct s_list
{
	int 			token;
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
    char *value;
    struct s_env *next; 
} t_env;

typedef struct s_vars
{
    int        c;
    int        c2;
    int        fd[2];
    int        x[2];
    char    *file_n;
    char    *value;
    int        st_in;
    t_list    *node;
    int        *id;
    // -- > add vars for cmds;
    
}    t_vars;


// ----- LISTS /////
t_list	*ft_lstnew(char *content, int tokn);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));

// ------- functions utils /////
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

//// ----- parsing ///
void tokenizer(char *str, char  **env);
int check_tok(t_list *token, int tok);


////// ------ syntax ////
int check_syntax(char *str);
int inside_limiters(char *str, char limiter, char c);
int limiter_stat(char *str, char limiter);
int check_tok(t_list *token, int tok);

////// --------- pipe ////
char	*search_for_path(char **env);
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
//char	*find_path(char *cmd, char **envp);
void	execute(char *argv, char **envp);
void 	execute_tb(char *cmds, char **env, t_list *node, int fd[2], int i[2]);
void	error(void);
int		open_file(char *argv, int i);
void	main_pipe(int num_com, char **str, char **env, t_list *node);
char	*get_path(char **envp);
char	*get_cmd(char *path, char **av, int i);
void	ft_freee(char **tabo, char *cmd);
char	*ft_path(char **env, char *cd);
void	ft_is_erreur(char **mycmd, char **mypath);

////------ builtins /////
void	ft_putstr_fd(char *s, int fd);
int 	ft_check_n(char *str,char *substr);
int		ft_echo(char **args);
int		ft_isalnum(char *str);
int 	ft_exit(char **str);
int		ft_atoi(const char *str);
void	ft_pwd();
t_env	*init_env(void *data);
t_env	*add_to_list(t_env *list,void *data);
t_env	*list_env(char **env);
void 	test_builtins(t_list *node,char **env);
void	ft_env(char **env);
char	**new_env_function(t_env *list);
void	ft_export(char **env);

/////// i dont know
int ft_execute_builtins(t_list *node, char **env);
void test_builtins(t_list *node,char **env);
char	*ft_path(char **env, char *cd);


#endif