/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:23:07 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/23 02:45:46 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_join_pipe(t_list *node, char **env)
{
	t_list	*head;
	char	*str;
	char	**str_split;
	int		num_com;

	str = ft_strdup("");
	head = node->next;
	while (head)
	{
		if (head->token == PIP)
			str = ft_strjoin(str, "|");
		else if (head->token == OUTPUTE_HEREDOC)
		{
			head = head->next;
			while (head->token == WSPACE && head->token != END_TOK)
				head = head->next;
		}
		else if (head->token == INTPUTE_HEREDOC)
			head = head->next;
		else if (head->token == OUTPUTE_REDI)
		{
			head = head->next;
			while (head->token == WSPACE && head->token != END_TOK)
				head = head->next;
		}
		else if (head->token == INPUTE_REDI)
		{
			head = head->next;
			while (head->token == WSPACE && head->token != END_TOK)
				head = head->next;
		}
		else if (head->token == WSPACE)
			str = ft_strjoin(str, "\v");
		else if (head->token == NUL)
			str = ft_strjoin(str, ft_strdup(" "));
		else if (head->token == WORD)
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	str_split = ft_split(str, '|');
	num_com = num_commande(str_split);
	free(str);
	main_pipe(num_com, str_split, env, node);
	exit(1);
}

void	execute_tb(char *cmds, char **env, t_list *node, t_vars var)
{
	char	*path;
	char	**cmd;
	int		end_p[2];
	int		a;
	int		k;

	a = 0;
	k = -1;
	while (cmds[++k])
	{
		if (cmds[k] == ' ' && cmds[k] != '\v')
			a = 1;
	}
	if (a)
		cmd = ft_split(cmds, ' ');
	else
		cmd = ft_split(cmds, '\v');
	if (check_tok(node, INTPUTE_HEREDOC))
	{
		if (!ft_is_last(node, INTPUTE_HEREDOC, INPUTE_REDI, END_TOK))
		{
			dup2(var.fdd[0], var.z[0]);
			close(var.fdd[0]);
		}
		else
		{
			if (pipe(end_p) == -1)
				perror("error");
			ft_putstr_fd(var.value, end_p[1]);
			close(end_p[1]);
			dup2(end_p[0], 0);
			close(end_p[0]);
		}
	}
	if (var.z[0] == 0)
	{
		dup2(var.fdd[0], var.z[0]);
		close(var.fdd[0]);
	}
	if (var.z[1] == 1)
	{
		dup2(var.fdd[1], var.z[1]);
		close(var.fdd[1]);
	}
	path = ft_path(env, cmds);
	if (access(cmd[0], X_OK) == 0)
		path = cmd[0];
	if (execve(path, cmd, env) == -1)
	{
		perror("Error");
		exit (1);
	}	
}

void	ft_execute_comnd(t_list *node, char **env)
{
	t_list	*head;
	t_vars	var;
	char	*str;
	int		pid;
	char	*file_n;
	char	**cmd;
	char	*p;
	int		wait_int;

	var.fdd[0] = dup(0);
	var.fdd[1] = dup(1);
	head = node;
	str = ft_strdup("");
	head = head->next;
	while (head)
	{
		if (head->token == WSPACE)
			str = ft_strjoin(str, "\v");
		else if (head->token == INPUTE_REDI)
		{	
			file_n = ft_strdup("");
			head = head->next;
			if (head->token == WSPACE)
				head = head->next;
			while (head->token == WORD && head->token != END_TOK)
			{
				file_n = ft_strjoin(file_n, head->content);
				head = head->next;
			}
			var.fdd[0] = open(file_n, O_RDONLY);
			if (var.fdd[0] == -1)
			{
				printf(" ---> %s <----- No such file or directory\n", file_n);
				return ;
			}
			free(file_n);
			var.z[0] = 0;
		}
		else if (head->token == INTPUTE_HEREDOC)
		{
			var.value = ft_strdup("");
			head = head->next;
			while (head->token == WSPACE && head->token != END_TOK)
				head = head->next;
			while (1)
			{
				p = readline("> ");
				if (!ft_strcmp_2(p, head->content))
					break ;
				p = ft_strjoin_nf(p, "\n");
				var.value = ft_strjoin(var.value, p);
				free(p);
			}
		}
		else if (head->token == OUTPUTE_HEREDOC)
		{
			file_n = ft_strdup("");
			head = head->next;
			if (head->token == WSPACE)
				head = head->next;
			while (head->token == WORD && head->token != END_TOK)
			{
				file_n = ft_strjoin(file_n, head->content);
				head = head->next;
			}
			var.fdd[1] = open(file_n, O_CREAT | O_WRONLY | O_APPEND, 0777);
			if (var.fdd[1] == -1)
			{
				printf(" %s Error in file creation\n", file_n);
				return ;
			}
			free(file_n);
			var.z[1] = 1;
		}
		else if (head->token == OUTPUTE_REDI)
		{
			file_n = ft_strdup("");
			head = head->next;
			if (head->token == WSPACE)
				head = head->next;
			while (head->token == WORD && head->token != END_TOK)
			{
				file_n = ft_strjoin(file_n, head->content);
				head = head->next;
			}
			var.fdd[1] = open(file_n, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (var.fdd[1] == -1)
			{
				printf(" %s Error in file creation\n", file_n);
				return ;
			}
			free(file_n);
			var.z[1] = 1;
		}
		else if (head->token == NUL)
			str = ft_strjoin(str, " ");
		else if (head->token == WORD)
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	cmd = ft_split(str, '\v');
	if (!cmd[0] || !str[0])
		return ;
	else
	{
		pid = fork();
		g_glob->g_pid = pid;
		if (pid == 0)
			execute_tb(str, env, node, var);
		else
			g_glob->status = 1;
		waitpid(pid, &wait_int, 0);
		status_child(wait_int);
	}
	free(str);
	ft_free(cmd);
}

void	tokenizer(char *str, char **env)
{
	int		i;
	int		j;
	pid_t	pid;
	t_list	*token;
	t_list	*head;

	i = 0;
	j = 1;
	if (str[0] == '\0')
		return ;
	token = ft_lstnew(ft_strdup("---"), START_TOK);
	head = token;
	if (!ft_create_tokens(&token, str))
		return ;
	// printf_list(head);
	// exit(0);
	// if (!check_syntax_list(head))
	// {
	// 	ft_error("syntax error ! \n", 0);
	// 	return ;
	// }
	if (check_tok(head, PIP))
	{
		pid = fork();
		if (pid == 0)
			ft_join_pipe(head, env);
		waitpid(pid, NULL, 0);
	}
	else if (ft_execute_builtins(head, env) == 1)
	{
		test_builtins(head, env);
	}
	else if (ft_execute_builtins(head, env) == 0)
	{
		ft_execute_comnd(head, env);
	}
	ft_lstclear(&head);
}
