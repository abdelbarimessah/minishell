/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:01:21 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/20 14:05:36 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_skip_node(t_list **node)
{
	while ((*node)->token != PIP && (*node))
	{
		if ((*node)->next->token == END_TOK)
			break ;
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

void	execute(char *argv, char **envp)
{
	int		i;
	char	**cmd;
	char	*path;

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

int	forkpipe(int *end)
{
	int	id;

	if (pipe(end) == -1)
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
