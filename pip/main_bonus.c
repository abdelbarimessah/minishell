/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:51:04 by amessah           #+#    #+#             */
/*   Updated: 2022/06/14 00:58:08 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void ft_skip_node(t_list **node)
{
	while ((*node)->token != PIP && (*node))
	{
		if ((*node)->next->token == END_TOK)
			break;
		(*node) = (*node)->next;
	}
	(*node) = (*node)->next;
}

int	is2or1(int i)
{
	if ((i % 2) == 0)
		return (1);
	else
		return (0);
}

int	ft_cheak(int i, char **cmd)
{
	if (!cmd[i + 1])
		return (2);
	else
		return (3);
	return (0);
}

void execute(char *argv, char **envp)
{
	int i;
	char **cmd;
	char *path;

	i = -1;
	cmd = ft_split(argv, '\v');
	path = ft_path(envp, cmd[0]);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}

int forkpipe(int *end)
{
	int id;
	if(pipe(end) == -1)
	{
		printf("error pipe\n");
		return (-1);
	}
	id = fork();
	if (id == -1)
	{
		printf("error fork\n");
		return (-1);
	}
	return (id);
}

int	ft_is_last(t_list *node, int c, int c2, int end)
{
	t_list	*head;
	int		nb;

	nb = 1;
	head = node;
	if (head->next)
		head = head->next;
	while (head->token != end)
	{
		if (head->token == c)
			nb = 1;
		else if (head->token == c2)
			nb = 0;
		head = head->next;
		if (!head)
			break ;
	}
	return (nb);
}

void ft_child_1(char *cmd, char **env, int *end_pipe, t_vars var)
{	
	if(check_tok_pip(var.node, INPUTE_REDI) && ft_is_last(var.node, INPUTE_REDI, INTPUTE_HEREDOC, PIP))
	{
		dup2(var.st_in, 0);
		close(var.st_in);
		dup2(var.fd[0], var.x[0]);
		close(var.fd[0]);
	}
	if(!var.c)
	{
		dup2(end_pipe[1], 1);
		close(end_pipe[0]);
		close(end_pipe[1]);
	}
	if(check_tok_pip(var.node, OUTPUTE_REDI) || check_tok_pip(var.node, OUTPUTE_HEREDOC))
	{
		dup2(var.fd[1], var.x[1]);
		close(var.fd[1]);
	}
	if(ft_execute_builtins(var.node, env))
		test_builtins(var.node, env);
	else
		execute(cmd, env);
}

void ft_child_2(char *cmd, char **env, t_vars var)
{
	if(check_tok_pip(var.node, INPUTE_REDI) && ft_is_last(var.node, INPUTE_REDI, INTPUTE_HEREDOC, PIP))
	{
		dup2(var.st_in, 0);
		close(var.st_in);
		dup2(var.fd[0], var.x[0]);
		close(var.fd[0]);
	}
	if (check_tok_pip(var.node, OUTPUTE_REDI) || check_tok_pip(var.node, OUTPUTE_HEREDOC))
	{
		dup2(var.fd[1], var.x[1]);
		close(var.fd[1]);
	}
	if(ft_execute_builtins(var.node, env))
		test_builtins(var.node, env);
	else
		execute(cmd, env);
}

void ft_child_3(char *cmd, char **env, int *end_pipe, t_vars var)
{
	if(check_tok_pip(var.node, INPUTE_REDI) && ft_is_last(var.node, INPUTE_REDI, INTPUTE_HEREDOC, PIP))
	{
		dup2(var.st_in, 0);
		close(var.st_in);
		dup2(var.fd[0], var.x[0]);
		close(var.fd[0]);
	}
	if(var.fd[1])
	{
		dup2(var.fd[1], var.x[1]);
		close(var.fd[1]);
	}
	else
	{
		dup2(end_pipe[1], 1);
		close(end_pipe[0]);
		close(end_pipe[1]);
	}
	if(ft_execute_builtins(var.node, env))
		test_builtins(var.node, env);
	else
		execute(cmd, env);
}

void main_pipe(int num_com, char **str, char **env, t_list *node)
{
	t_vars var;
	int end_pipe[2];
	int i;
	t_list *head;
	char *p;

	i = -1;
	var.file_n = ft_strdup("");
	var.id = malloc(num_com * sizeof(int));
	var.st_in = dup(0);
	var.st_out = dup(1);
	while(str[++i])
	{
		var.node = node;
		var.c = 0;
		var.c2 = 0;
		head = node;
		while(head && head->token != PIP)
		{
			if (head->token == OUTPUTE_REDI)
			{
				var.file_n = ft_strdup("");
				head = head->next;
				if (head->token == WSPACE)
					head = head->next;
				while (head->token == WORD && head->token != END_TOK)
				{
					var.file_n = ft_strjoin(var.file_n, head->content);
					head = head->next;
				}
				var.fd[1] = open(var.file_n, O_CREAT | O_RDWR | O_TRUNC, 0777);
				if (var.fd[1] == -1) 
				{
					printf(" ---> %s <----- Error in file creation\n", var.file_n);
					break ;
				}
				free(var.file_n);
				var.x[1] = 1;
			}
			else if(head->token == OUTPUTE_HEREDOC)
			{
				var.file_n = ft_strdup("");
				head = head->next;
				if (head->token == WSPACE)
					head = head->next;
				while (head->token == WORD && head->token != END_TOK)
				{
					var.file_n = ft_strjoin(var.file_n, head->content);
					head = head->next;
				}
				var.fd[1] = open(var.file_n, O_CREAT | O_WRONLY | O_APPEND, 0777);
				if (var.fd[1] == -1)
				{
					printf(" ---> %s <----- Error in file creation\n", var.file_n);
					break ;
				}
				free(var.file_n);
				var.x[1] = 1;
			}
			else if(head->token == INTPUTE_HEREDOC)
			{
				var.value = ft_strdup("");
				head = head->next;
				while(head->token == WSPACE && head->token != END_TOK)
					head = head->next;
				dup2(var.st_in, 0);
				while(1)
				{
					p = readline("> ");
					if(!ft_strcmp(p , head->content))
						break ;
					p = ft_strjoin_nf(p, "\n");
					var.value = ft_strjoin(var.value, p);
					free(p);
				}
			}
			else if (head->token == INPUTE_REDI)
			{
				var.file_n = ft_strdup("");
				head = head->next;
				if (head->token == WSPACE)
					head = head->next;
				while (head->token == WORD && head->token != END_TOK)
				{
					var.file_n = ft_strjoin(var.file_n, head->content);
					head = head->next;
				}
				var.fd[0] = open(var.file_n, O_RDONLY);
				if (var.fd[0] == -1)
				{
					printf(" ---> %s <----- Error in file opening\n", var.file_n);
					break ;
				}
				free(var.file_n);
				var.x[0] = 0;
			}
			else 
				head = head->next;
		}
		if(check_tok_pip(node, INTPUTE_HEREDOC) && var.value)
		{
			if(pipe(end_pipe) == -1)
				perror("Error");
			ft_putstr_fd(var.value, end_pipe[1]);
			close(end_pipe[1]);
			dup2(end_pipe[0], 0);
			close(end_pipe[0]);
		}
		var.id[i] = forkpipe(end_pipe);
		if(var.id[i] == -1)
			exit(1);
		if(var.id[i] == 0)
		{
			if(!str[i + 1])
				var.c2 = 1;
			if(i == 0)
				ft_child_1(str[i], env, end_pipe, var);
			else if (ft_cheak(i, str) == 2)
				ft_child_2(str[i], env, var);
			else if(ft_cheak(i, str) == 3)
				ft_child_3(str[i], env, end_pipe, var);
		}
		if(i == 0 && !check_tok(node, INTPUTE_HEREDOC))
			var.c = var.id[i];
		ft_skip_node(&node);
		dup2(end_pipe[0], 0);
		close(end_pipe[1]);
		close(end_pipe[0]);
		var.fd[0] = 0;
		var.fd[1] = 0;
	} 
	waitpid(var.c, NULL, 0);
	while(i != -1)
	{
		waitpid(var.id[i], NULL, 0);
		i--;
	}
	ft_free(str);
}
