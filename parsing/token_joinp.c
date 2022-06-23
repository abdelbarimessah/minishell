/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_joinp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:35:49 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/23 22:39:02 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_in(t_vars *var)
{
	dup2(var->fdd[0], var->z[0]);
	close(var->fdd[0]);
}

void	dup_out(t_vars *var)
{
	dup2(var->fdd[1], var->z[1]);
	close(var->fdd[1]);
}

void	error_jp(void)
{
	perror("Error");
	exit (1);
}

int	check_order(t_list **node, t_vars *var)
{
	if (!ft_is_last((*node), INTPUTE_HEREDOC, INPUTE_REDI, END_TOK))
		dup_in(var);
	else
	{
		if (pipe(var->extb_end_p) == -1)
			perror("error");
		ft_putstr_fd(var->value, var->extb_end_p[1]);
		close(var->extb_end_p[1]);
		dup2(var->extb_end_p[0], 0);
		close(var->extb_end_p[0]);
	}
	return (1);
}

void	execute_tb(char *cmds, char **env, t_list *node, t_vars var)
{
	var.extb_a = 0;
	var.extb_a = -1;
	while (cmds[++var.extb_a])
	{
		if (cmds[var.extb_a] == ' ' && cmds[var.extb_a] != '\v')
			var.extb_a = 1;
	}
	if (var.extb_a)
		var.extb_cmd = ft_split(cmds, ' ');
	else
		var.extb_cmd = ft_split(cmds, '\v');
	if (check_tok(node, INTPUTE_HEREDOC))
	{
		if (!check_order(&node, &var))
			return ;
	}
	if (var.z[0] == 0)
		dup_in(&var);
	if (var.z[1] == 1)
		dup_out(&var);
	var.extb_path = ft_path(env, cmds);
	if (access(var.extb_cmd[0], X_OK) == 0)
		var.extb_path = var.extb_cmd[0];
	if (execve(var.extb_path, var.extb_cmd, env) == -1)
		error_jp();
}
