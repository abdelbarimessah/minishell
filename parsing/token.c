/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:23:07 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/25 23:16:48 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_tb(char *cmds, char **env, t_list *node, t_vars var)
{
	var.jp_a = 0;
	var.jp_k = -1;
	while (cmds[++var.jp_k])
	{
		if (cmds[var.jp_k] == ' ' && cmds[var.jp_k] != '\v')
			var.jp_a = 1;
	}
	if (var.jp_a)
		var.jp_cmd = ft_split(cmds, ' ');
	else
		var.jp_cmd = ft_split(cmds, '\v');
	if (check_tok(node, INTPUTE_HEREDOC))
	{
		if (!check_toorder(&var, &node))
			return ;
	}
	if (var.z[0] == 0)
		dup_in(&var);
	if (var.z[1] == 1)
		dup_out(&var);
	var.jp_path = ft_path(env, cmds);
	if (access(var.jp_cmd[0], X_OK) == 0)
		var.jp_path = var.jp_cmd[0];
	if (execve(var.jp_path, var.jp_cmd, env) == -1)
		ft_pereor();
}

void	tokenizer(char *str, char **env)
{
	pid_t	pid;
	t_list	*token;
	t_list	*head;

	if (str[0] == '\0')
		return ;
	token = ft_lstnew(ft_strdup("---"), START_TOK);
	head = token;
	if (!ft_create_tokens(&token, str))
		return ;
	if (check_tok(head, PIP))
	{
		pid = fork();
		if (pid == 0)
			ft_join_pipe(head, env);
		waitpid(pid, NULL, 0);
	}
	else if (ft_execute_builtins(head, env) == 1)
		test_builtins(head, env);
	else if (ft_execute_builtins(head, env) == 0)
		ft_execute_comnd(head, env);
	ft_lstclear(&head);
}
