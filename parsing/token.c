/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:23:07 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/12 16:44:37 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_str(char *str, int i)
{
	if(str[i] && str[i] != '|' && str[i] != '&' && str[i] != ' '
		&& str[i] != '\'' && str[i] != '"'  && str[i] != '$'
		&& str[i] != '(' && str[i] != ')' && str[i] != '>' && str[i] != '<')
		return(1);
	else
	{
		if(str[i] == '&' && str[i + 1] != '&')
			return(1);
		else
			return(0);
	}
}

int check_tok(t_list *token, int tok)
{
	t_list *head;
	head = token;

	while(head)
	{
		if(head->token == tok)
			return (1);
		head = head->next;
	}
	return (0);
}

int check_tok_pip(t_list *token, int tok)
{
	t_list *head;

	head = token;
	while (head)
	{
		if(head->token == PIP)
			break;
		if(head->token == tok)
			return(1);
		head = head->next;
	}
	return(0);
}

int ft_checker1(t_list **node, char *str, int i, char **env)
{
	int j;
	int c;
	int n;
	int x;
	char *s;
	char *stri;
	
	j = i;
	if(str[j] == '"' && str[j + 1] == '"')
		return (0);
	while(str[++j])
	{
		if(str[j] == '"')
			break ;
	}
	if(str[j] == '"')
	{
		i++;
		stri = ft_substr(str, i, j - i);
		x = i;
		
		if(ft_strchr(str, '$'))
		{
			c = i - 1;
			while(++c < j)
			{
				if(str[c] == '$')
				{
					if(c - x)
						ft_lstadd_back(node, ft_lstnew(ft_substr(str, x, c - x), WORD));
					n = c++;
					while(check_str(str, c))
						c++;
					s = get_from_env(env, ft_substr(str, n + 1, c - (n + 1)));
					if(s)
						ft_lstadd_back(node, ft_lstnew(ft_strdup(s), WORD));
					x = c;
					c--;
				}
			}
			if(j - x)
				ft_lstadd_back(node, ft_lstnew(ft_substr(str, x, j - x), WORD));
			free(stri);
		}
		else
			ft_lstadd_back(node, ft_lstnew(stri, WORD));
		return (j - i + 1);
	}
	return(printf("double quotes not closed !\n"), -1);
}

int ft_checker2(t_list **node, char *str, int i)
{
	int j;

	j = i;
	if(str[j] == '\'' && str[j + 1] == '\'')
		return (0);
	while(str[++j])
	{
		if(str[j] == '\'')
			break ;
	}
	if(str[j] == '\'')
	{
		i++;
		ft_lstadd_back(node, ft_lstnew(ft_substr(str, i, j - i), WORD));
		return (j - i + 1);
	}
	return (-1);
}

int ft_create_tokens(struct s_list **node, char *str, char **env) 
{
	int i;
	int j;
	char *s;
	t_env *tmp;
	char **env1;
	(void)env;
	i = 0;
	j = 1;
	
	tmp = g_glob;
	env1 = new_env_function(tmp);
	while(str[i] == ' ')
		i++;
	while(i < ft_strlen(str))
	{
		j = 0;
		if(str[i] == ' ')
		{
			while(str[i] == ' ')
				i++;
			if(!str[i])
				break;
			ft_lstadd_back(node, ft_lstnew(ft_strdup(" "), SPACE));
			i--;
		}
		else if(str[i] == '|')
			ft_lstadd_back(node, ft_lstnew(ft_strdup("|"), PIP));
		else if(str[i] == '"')
		{
			j = ft_checker1(node, str, i, env1);
			if(j == -1)
				return (0);
			i += j + 1;
		}
		else if(str[i] == '\'')
		{
			j = ft_checker2(node, str, i);
			if( j == -1)
			{
				printf("single quotes not closed !\n");
				return 0;
			}
			i += j + 1;
		}
		else if(str[i] == '$')
		{
			if(!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '$')
			{
				ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WORD));
				i++;
			}
			else if (str[i + 1] == '?')
			{
				ft_lstadd_back(node, ft_lstnew(ft_strdup(ft_itoa(g_glob->exit_status)), WORD));
				i++;
			}
			else
			{
				j = i + 1;
				while(check_str(str, j))
					j++;
				s = get_from_env(env1, ft_substr(str, i + 1, j - (i + 1)));
				if(s)
					ft_lstadd_back(node, ft_lstnew(ft_strdup(s), WORD));
				i += (j - i);
			}
		}
		else if(str[i] == '>' && str[i + 1] == '>')
		{
			i++;
			ft_lstadd_back(node, ft_lstnew(ft_strdup(">>"), OUTPUTE_HEREDOC));
		}
		else if(str[i] == '>' && str[i + 1] != '>')
			ft_lstadd_back(node, ft_lstnew(ft_strdup(">"), OUTPUTE_REDI));
		else if(str[i] == '<')
			ft_lstadd_back(node, ft_lstnew(ft_strdup("<"), INPUTE_REDI));
		else
		{
			if(str[i] != ' ')
			{
				i--;
				while(check_str(str, ++i))
					j++;
				ft_lstadd_back(node, ft_lstnew(ft_substr(str,  i - j, j), WORD));
			}

		}
		if(!j)
			i++;
	}
	ft_lstadd_back(node, ft_lstnew(ft_strdup("---"), END_TOK));
	
	return (1);
}

void	printf_list(t_list *lst)
{
	while (lst)
	{
		printf("%d - %s\n", lst->token, lst->content);
		lst = lst->next;
	}
	puts("");
}

int num_commande(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void ft_join_pipe(t_list *node, char **env)
{
	t_list *head;
	char *str;
	char **str_split;
	int num_com;
	
	str = ft_strdup("");
	head = node->next;
	while(head)
	{
		if(head->token == PIP)
			str = ft_strjoin(str, "|");
		else if(head->token == OUTPUTE_HEREDOC)
		{
			head = head->next;
			while(head->token == SPACE && head->token != END_TOK)
				head = head->next;
		}
		else if(head->token == OUTPUTE_REDI)
		{
			head = head->next;
			while(head->token == SPACE && head->token != END_TOK)
				head = head->next;
		}
		else if(head->token == INPUTE_REDI)
		{
			head = head->next;
			while(head->token == SPACE && head->token != END_TOK)
				head = head->next;
		}
		else if(head->token == SPACE)
			str = ft_strjoin(str, "\v");
		else if(head->token == WORD)
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	str_split = ft_split(str, '|');
	num_com = num_commande(str_split);
	free(str);
	main_pipe(num_com, str_split, env, node);
	exit(1);
}

int ft_execute_builtins(t_list *node, char **env)
{
	t_list *head;
	char *str;
	char **cmd;
	int c;

	(void)env;
	str = ft_strdup("");
	head = node->next;
	c = 0;
	while(head->token != END_TOK)
	{
		if(head->token == SPACE)
			str = ft_strjoin(str, "\v");
		else if(head->token == OUTPUTE_REDI)
			return (0);
		else if(head->token == INPUTE_REDI)
			return (0);
		else if(head->token == OUTPUTE_HEREDOC)
			return (0);
		else if(head->content)
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	if(!str[0])
		return (0);
	cmd = ft_split(str, '\v');
	free(str);
	if(!strcmp(cmd[0], "echo"))
	{
		ft_free(cmd);
		return (1);
	}
	if(!strcmp(cmd[0], "cd"))
	{
		ft_free(cmd);
		return (1);
	}
	if(!strcmp(cmd[0], "export"))
	{
		ft_free(cmd);
		return (1);
	}
	if(!strcmp(cmd[0], "unset"))
	{
		ft_free(cmd);
		return (1);
	}
	if(!strcmp(cmd[0], "pwd"))
	{
		ft_free(cmd);
		return (1);
	}
	if(!strcmp(cmd[0], "env"))
	{
		ft_free(cmd);
		return (1);
	}
	if(!strcmp(cmd[0], "exit"))
	{
		ft_free(cmd);
		return (1);
	}
	ft_free(cmd);
	return (0);
}

void execute_tb(char *cmds, char **env, t_list *node, int fd[2], int i[2])
{
	char *path;
	char **cmd;
	(void)node;
	
	cmd = ft_split(cmds, '\v');
	if(i[0] == 0)
	{
		dup2(fd[0], i[0]);
		close(fd[0]);
	}
	if(i[1] == 1)
	{
		dup2(fd[1], i[1]);
		close(fd[1]);
	}
	path = ft_path(env, cmds);
	if(access(cmd[0], X_OK) == 0)
		path = cmd[0];
	if(execve(path, cmd, env) == -1)
	{
		perror("Error");
		exit (1);
	}	
}

void ft_execute_comnd(t_list *node, char **env)
{
	t_list *head;
	char *str;
	int pid;
	int fd[2];
	char *file_n;
	int i[2];
	char **cmd;
	
	head = node;
	str = ft_strdup("");
	head = head->next;
	while(head)
	{
		if(head->token == SPACE)
			str = ft_strjoin(str, "\v");
		else if(head->token == INPUTE_REDI)
		{	
			file_n = ft_strdup("");
			head = head->next;
			if(head->token == SPACE)
				head = head->next;
			while(head->token == WORD && head->token != END_TOK)
			{
				file_n = ft_strjoin(file_n, head->content);
				head = head->next;
			}
			fd[0] = open(file_n, O_RDONLY);
			if(fd[0] == -1)
			{
				printf(" ---> %s <----- No such file or directory\n", file_n);
				return ;
			}
			free(file_n);
			i[0] = 0;
		}
		else if(head->token == OUTPUTE_HEREDOC)
		{
			file_n = ft_strdup("");
			head = head->next;
			if(head->token == SPACE)
				head = head->next;
			while(head->token == WORD && head->token != END_TOK)
			{
				file_n = ft_strjoin(file_n, head->content);
				head = head->next;
			}
			fd[1] = open(file_n, O_CREAT | O_WRONLY | O_APPEND, 0777);
			if(fd[1] == -1)
			{
				printf(" ---> %s <----- Error in file creation\n", file_n);
				return ;
			}
			free(file_n);
			i[1] = 1;
		}
		else if(head->token == OUTPUTE_REDI)
		{
			file_n = ft_strdup("");
			head = head->next;
			if(head->token == SPACE)
				head = head->next;
			while(head->token == WORD && head->token != END_TOK)
			{
				file_n = ft_strjoin(file_n, head->content);
				head = head->next;
			}
			fd[1] = open(file_n, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if(fd[1] == -1)
			{
				printf(" ---> %s <----- Error in file creation\n", file_n);
				return ;
			}
			free(file_n);
			i[1] = 1;
		}
		else if(head->token == WORD)
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	cmd = ft_split(str, '\v');
	if(!str[0])
		return ;
	else
	{
		pid = fork();
		if(pid == 0)
			execute_tb(str, env, head, fd, i);
		waitpid(pid, NULL, 0);
	}
	fd[0] = 0;
	fd[1] = 0;
	free(str);
	ft_free(cmd);
}

void tokenizer(char *str, char  **env)
{
	int i;
	int j;
	pid_t pid;
	t_list *token;
	t_list *head;
	
	i = 0;
	j = 1;
	if(str[0] == '\0')
		return;
	token = ft_lstnew(ft_strdup("---"), START_TOK);
	head = token;
	if(!ft_create_tokens(&token, str, env))
		return ;
	if(check_tok(head, PIP))
	{
		pid = fork();
		if(pid == 0)
			ft_join_pipe(head, env);
		waitpid(pid, NULL, 0);
	}

	else if(ft_execute_builtins(head, env) == 1)
	{
		test_builtins(head, env);	
	}
	else if(!ft_execute_builtins(head, env))
	{
		ft_execute_comnd(head, env);
	}
	ft_lstclear(&token);
} 