/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:51:04 by amessah           #+#    #+#             */
/*   Updated: 2022/06/22 17:04:32 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_pipe(int num_com, char **str, char **env, t_list *node)
{
	t_vars	var;
	int		end_pipe[2];
	int		i;
	t_list	*head;

	i = -1;
	var.id = malloc(num_com * sizeof(int));
	var.st_in = dup(0);
	var.st_out = dup(1);
	while (str[++i])
	{
		var.node = node;
		var.c = 0;
		var.c2 = 0;
		head = node;
		loop_list(&head, &var);
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
