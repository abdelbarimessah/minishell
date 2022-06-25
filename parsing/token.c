/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:23:07 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/25 21:12:45 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch_exec(t_list **head, char **env)
{
	int	state;

	state = ft_execute_builtins(*head, env);
	if (state == 1)
		test_builtins(*head, env);
	if (state == 0)
		ft_execute_comnd(*head, env);
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
	if (!ft_create_tokens(&token, str, env))
		return ;
	if (check_tok(head, PIP))
	{
		pid = fork();
		if (pid == 0)
			ft_join_pipe(head, env);
		waitpid(pid, NULL, 0);
	}
	launch_exec(&head, env);
	ft_lstclear(&head);
}
