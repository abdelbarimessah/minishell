/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:23:07 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/23 22:46:41 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenizer(char *str, char **env)
{
	int		i;
	int		j;
	pid_t	pid;
	t_list	*token;
	t_list	*head;
	int state;

	i = 0;
	j = 1;
	if (str[0] == '\0')
		return ;
	token = ft_lstnew(ft_strdup("---"), START_TOK);
	head = token;
	if (!ft_create_tokens(&token, str))
		return ;
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
	state = ft_execute_builtins(head, env);
	if (state == 1)
		test_builtins(head, env);
	else if (state == 0)
		ft_execute_comnd(head, env);
	ft_lstclear(&head);
}
