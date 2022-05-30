/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:38 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/28 17:35:25 by ntanjaou         ###   ########.fr       */
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
} t_token_type;

typedef struct s_list
{
	int 			token;
	char			*content;
	struct s_list	*next;
}	t_list;


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

//// ----- parsing ///
void tokenizer(char *str, char  **env);


////// ------ syntax ////
int check_syntax(char *str);
int inside_limiters(char *str, char limiter, char c);
int limiter_stat(char *str, char limiter);


#endif