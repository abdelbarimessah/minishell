/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:51:04 by amessah           #+#    #+#             */
/*   Updated: 2022/06/21 22:16:04 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int outp_redi(t_list **nod, t_vars var)
{
	var.file_n = ft_strdup("");
	(*nod) = (*nod)->next;
	if ((*nod)->token == WSPACE)
		(*nod) = (*nod)->next;
	while ((*nod)->token == WORD && (*nod)->token != END_TOK)
	{
		var.file_n = ft_strjoin(var.file_n, (*nod)->content);
		(*nod) = (*nod)->next;
	}
	var.fd[1] = open(var.file_n, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (var.fd[1] == -1)
	{
		printf(" %s Error in file creation\n", var.file_n);
		return (0);
	}
	free(var.file_n);
	return (var.fd[1]);
}

int outp_herdc(t_list **nod, t_vars var)
{
	var.file_n = ft_strdup("");
	(*nod) = (*nod)->next;
	if ((*nod)->token == WSPACE)
		(*nod) = (*nod)->next;
	while ((*nod)->token == WORD && (*nod)->token != END_TOK)
	{
		var.file_n = ft_strjoin(var.file_n, (*nod)->content);
		(*nod) = (*nod)->next;
	}
	var.fd[1] = open(var.file_n, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (var.fd[1] == -1)
	{
		printf(" %s Error in file creation\n", var.file_n);
		return (0);
	}
	free(var.file_n);
	return (var.fd[1]);
}

void her_dc(t_list **nod, t_vars var)
{
	char *p;

	var.value = ft_strdup("");
	(*nod) = (*nod)->next;
	while ((*nod)->token == WSPACE && (*nod)->token != END_TOK)
		(*nod) = (*nod)->next;
	dup2(var.st_in, 0);
	while (1)
	{
		p = readline("> ");
		if (!ft_strcmp(p, (*nod)->content))
			break ;
		p = ft_strjoin_nf(p, "\n");
		var.value = ft_strjoin(var.value, p);
		free(p);
	}
}

void	main_pipe(int num_com, char **str, char **env, t_list *node)
{
	t_vars	var;
	int		end_pipe[2];
	int		i;
	t_list	*head;
	//char	*p;

	i = -1;
	var.file_n = ft_strdup("");
	var.id = malloc(num_com * sizeof(int));
	var.st_in = dup(0);
	var.st_out = dup(1);
	while (str[++i])
	{
		var.node = node;
		var.c = 0;
		var.c2 = 0;
		head = node;
		while (head && head->token != PIP)
		{
			if (head->token == OUTPUTE_REDI)
			{
				var.fd[1] = outp_redi(&head, var);
				printf("%d \n", var.fd[1]);
				if(!var.fd[1])
					break ;
			}
			else if (head->token == OUTPUTE_HEREDOC)
			{
				var.fd[1] = outp_herdc(&head, var);
				if(!var.fd[1])
					break ;
			}
			else if (head->token == INTPUTE_HEREDOC)
			{
				// var.value = ft_strdup("");
				// head = head->next;
				// while (head->token == WSPACE && head->token != END_TOK)
				// 	head = head->next;
				// dup2(var.st_in, 0);
				// while (1)
				// {
				// 	p = readline("> ");
				// 	if (!ft_strcmp(p, head->content))
				// 		break ;
				// 	p = ft_strjoin_nf(p, "\n");
				// 	var.value = ft_strjoin(var.value, p);
				// 	free(p);
				// }
				her_dc(&head, var);
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
					printf(" %s Error in file opening\n", var.file_n);
					break ;
				}
				free(var.file_n);
			}
			else
				head = head->next;
		}
		if (check_tok_pip(node, INTPUTE_HEREDOC) && var.value)
		{
			if (pipe(end_pipe) == -1)
				perror("Error");
			ft_putstr_fd(var.value, end_pipe[1]);
			close(end_pipe[1]);
			dup2(end_pipe[0], 0);
			close(end_pipe[0]);
		}
		var.id[i] = forkpipe(end_pipe);
		g_glob->g_pid = var.id[i];
		if (var.id[i] == -1)
			exit(1);
		if (var.id[i] == 0)
		{
			if (!str[i + 1])
				var.c2 = 1;
			if (i == 0)
				ft_child_1(str[i], env, end_pipe, var);
			else if (ft_cheak(i, str) == 2)
				ft_child_2(str[i], env, var);
			else if (ft_cheak(i, str) == 3)
				ft_child_3(str[i], env, end_pipe, var);
		}
		if (i == 0 && !check_tok(node, INTPUTE_HEREDOC))
			var.c = var.id[i];
		ft_skip_node(&node);
		dup2(end_pipe[0], 0);
		close(end_pipe[1]);
		close(end_pipe[0]);
		var.fd[0] = 0;
		var.fd[1] = 0;
	}
	waitpid(var.c, NULL, 0);
	while (i != -1)
	{
		waitpid(var.id[i], NULL, 0);
		i--;
	}
	ft_free(str);
}
