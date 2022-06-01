/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:23:07 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/01 14:55:59 by ntanjaou         ###   ########.fr       */
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

int ft_checker1(t_list **node, char *str, int i, char **env)
{
	int j;
	int c;
	int n;
	char *s;
	
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
		c = i - 1;
		while(++c < j)
		{
			if(str[c] == '$')
				break;
		}
		if(str[c] == '$')
		{
			ft_lstadd_back(node, ft_lstnew(ft_substr(str, i, c - i), WORD));
			n = c++;
			while(check_str(str, c))
				c++;
			s = get_from_env(env, ft_substr(str, n + 1, c - (n + 1)));
			ft_lstadd_back(node, ft_lstnew(ft_strdup(s), WORD));
			n = c;
			while(c < j)
				c++;
			ft_lstadd_back(node, ft_lstnew(ft_substr(str, n, c - n), WORD));
		}
		else
			ft_lstadd_back(node, ft_lstnew(ft_substr(str, i, j - i), WORD));
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

	i = 0;
	j = 1;
	
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
			j = ft_checker1(node, str, i, env);
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
			if(!str[i + 1] || str[i + 1] == ' ')
				ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WORD));
			else
			{
				j = i + 1;
				while(check_str(str, j))
					j++;
				s = get_from_env(env, ft_substr(str, i + 1, j - (i + 1)));
				ft_lstadd_back(node, ft_lstnew(ft_strdup(str), WORD));
				i += (j - i);
			}
		}
		else if(str[i] == '>')
			ft_lstadd_back(node, ft_lstnew(ft_strdup(">"), OUTPUTE_REDI));
		else if(str[i] == '<')
			ft_lstadd_back(node, ft_lstnew(ft_strdup("<"), INPUTE_REDI));
		else
		{
			i--;
			while(check_str(str, ++i))
				j++;
			ft_lstadd_back(node, ft_lstnew(ft_substr(str,  i - j, j), WORD));
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
	// t_list *right_side;
	char *str;
	char **str_split;
	int num_com;
	// int i;
	
	// i = 0;
	(void)env;
	str = ft_strdup("");
	head = node->next;
	printf_list(head);
	while(head->token != END_TOK)
	{
		if(head->token == PIP)
			str = ft_strjoin(str, "|");
		else if(head->token == SPACE)
			str = ft_strjoin(str, " ");
		else
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	str_split = ft_split(str, '|');
	// while(str_split[0][i])
	// {
	// 	if(str[0][i] == '<' || str[0][i] == '>')
	// 	{
	// 		right_side = 
	// 	}
	// 	i++;
	// }
	num_com = num_commande(str_split);
	free(str);
	main_pipe(num_com, str_split, env, head);
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
			str = ft_strjoin(str, " ");
		else if(head->token == OUTPUTE_REDI)
			return (0);
		else if(head->token == INPUTE_REDI)
			return (0);
		else if(head->content)
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	if(!str[0])
		return (0);
	cmd = ft_split(str, ' ');
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
	ft_free(cmd);
	return (0);
}

void execute_tb(char *cmds, char **env, t_list *node, int fd[2], int i[2])
{
	char *path;
	char **cmd;

	(void)node;
	cmd = ft_split(cmds, ' ');
	if(i[0] == 0 && i[1] == 1)
	{
		dup2(fd[0], i[0]);
		close(fd[0]);
		dup2(fd[1], i[1]);
		close(fd[1]);
	}
	else if(i[0] == 0)
	{
		dup2(fd[0], i[0]);
		close(fd[0]);
	}
	else if(i[1] == 1)
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
			str = ft_strjoin(str, " ");
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
			// i[1] = -1;
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
			// i[0] = -1;
			i[1] = 1;
		}
		else if(head->token == WORD)
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	cmd = ft_split(str, ' ');
	if(!str[0])
		return ;
	else
	{	
		pid = fork();
		if(pid == 0)
			execute_tb(str, env, head, fd, i);
		waitpid(pid, NULL, 0);
	}
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
		test_builtins(head, env);
	else if(!ft_execute_builtins(head, env))
		ft_execute_comnd(head, env);
	ft_lstclear(&token);
}