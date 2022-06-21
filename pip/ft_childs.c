/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:06:53 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/21 22:20:08 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_child_1(char *cmd, char **env, int *end_pipe, t_vars var)
{	
	if (check_tok_pip(var.node, INPUTE_REDI)
		&& ft_is_last(var.node, INPUTE_REDI, INTPUTE_HEREDOC, PIP))
	{
		dup2(var.st_in, 0);
		close(var.st_in);
		dup2(var.fd[0], 0);
		close(var.fd[0]);
	}
	if (!var.c)
	{
		dup2(end_pipe[1], 1);
		close(end_pipe[0]);
		close(end_pipe[1]);
	}
	if (check_tok_pip(var.node, OUTPUTE_REDI)
		|| check_tok_pip(var.node, OUTPUTE_HEREDOC))
	{
		dup2(var.fd[1], 1);
		close(var.fd[1]);
	}
	if (ft_execute_builtins(var.node, env))
		test_builtins(var.node, env);
	else
		execute(cmd, env);
}

void	ft_child_2(char *cmd, char **env, t_vars var)
{
	
	if (check_tok_pip(var.node, INPUTE_REDI)
		&& ft_is_last(var.node, INPUTE_REDI, INTPUTE_HEREDOC, PIP))
	{
		dup2(var.st_in, 0);
		close(var.st_in);
		dup2(var.fd[0], 0);
		close(var.fd[0]);
	}
	if (check_tok_pip(var.node, OUTPUTE_REDI)
		|| check_tok_pip(var.node, OUTPUTE_HEREDOC))
	{
		dup2(var.fd[1], 1);
		close(var.fd[1]);
	}
	if (ft_execute_builtins(var.node, env))
		test_builtins(var.node, env);
	else
		execute (cmd, env);
}

void	ft_child_3(char *cmd, char **env, int *end_pipe, t_vars var)
{
	if (check_tok_pip(var.node, INPUTE_REDI)
		&& ft_is_last(var.node, INPUTE_REDI, INTPUTE_HEREDOC, PIP))
	{
		dup2(var.st_in, 0);
		close(var.st_in);
		dup2(var.fd[0], 0);
		close(var.fd[0]);
	}
	if (var.fd[1])
	{
		dup2(var.fd[1], 1);
		close(var.fd[1]);
	}
	else
	{
		dup2(end_pipe[1], 1);
		close(end_pipe[0]);
		close(end_pipe[1]);
	}
	if (ft_execute_builtins(var.node, env))
		test_builtins(var.node, env);
	else
		execute(cmd, env);
}
