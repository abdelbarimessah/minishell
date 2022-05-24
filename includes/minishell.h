/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:38 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/24 18:15:14 by ntanjaou         ###   ########.fr       */
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

typedef enum e_token_type
{
	pip,
	single_quote,
	double_quote,
	white_space,
	dollar,
	simple_redi_left,
	simple_redi_right,
	double_redi_left,
	double_redi_right,
	general_word,	
} t_token_type;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_token
{
	char value;
	char *value_concat;
	t_token_type type;
} t_token;

typedef struct s_info
{
	char **info_env;
	char *path;
	t_list *list_input_token;
} t_info;

t_info g_info;

// ----- LISTS /////
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),	void (*del)(void *));

// ------- functions utils /////
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_free(char **str);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strtrim(char *s1, char *set);
char	*get_path(char **envp);
int		ft_strlcpy(char *dest, char *src, int size);
char	*ft_strchrr(char *str, int c);

//// ----- parsing ///
void tokenizer(char *str);
void clear_token(void *content);






#endif