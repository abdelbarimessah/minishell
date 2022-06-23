/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:51:04 by amessah           #+#    #+#             */
/*   Updated: 2022/06/23 02:21:56 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pip_herdc(int pip[2], t_vars *var)
{
	if (pipe(pip) == -1)
		perror("Error");
	ft_putstr_fd(var->value, pip[1]);
	close(pip[1]);
	dup2(pip[0], 0);
	close(pip[0]);
}

void	re_initialize(int pip[2], t_vars *var)
{
	dup2(pip[0], 0);
	close(pip[1]);
	close(pip[0]);
	var->fd[0] = 0;
	var->fd[1] = 0;
}

void	call_childs(char **str, int end_pipe[2], char **env, t_vars *var)
{
	if (!str[var->main_pi + 1])
		var->c2 = 1;
	if (var->main_pi == 0)
		ft_child_1(str[var->main_pi], env, end_pipe, *var);
	else if (ft_cheak(var->main_pi, str) == 2)
		ft_child_2(str[var->main_pi], env, *var);
	else if (ft_cheak(var->main_pi, str) == 3)
		ft_child_3(str[var->main_pi], env, end_pipe, *var);
}

void	init_pip(t_list **node, t_vars *var, char **env, char **str)
{
	int		end_pipe[2];
	t_list	*head;

	var->node = *node;
	var->c = 0;
	var->c2 = 0;
	head = *node;
	loop_list(&head, var);
	if (check_tok_pip(*node, INTPUTE_HEREDOC) && var->value)
		pip_herdc(end_pipe, var);
	var->id[var->main_pi] = forkpipe(end_pipe);
	// g_glob->g_pid = var->id[var->main_pi];
	if (var->id[var->main_pi] == -1)
		exit(1);
	if (var->id[var->main_pi] == 0)
		call_childs(str, end_pipe, env, var);
	if (var->main_pi == 0 && !check_tok(*node, INTPUTE_HEREDOC))
		var->c = var->id[var->main_pi];
	ft_skip_node(node);
	re_initialize(end_pipe, var);
}

void	main_pipe(int num_com, char **str, char **env, t_list *node)
{
	t_vars	var;

	var.main_pi = -1;
	var.id = malloc(num_com * sizeof(int));
	var.st_in = dup(0);
	var.st_out = dup(1);
	while (str[++var.main_pi])
		init_pip(&node, &var, env, str);
	waitpid(var.c, NULL, 0);
	while (var.main_pi != -1)
	{
		waitpid(var.id[var.main_pi], NULL, 0);
		var.main_pi--;
	}
	ft_free(str);
}
