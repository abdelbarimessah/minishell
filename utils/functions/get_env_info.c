/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:28:18 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/21 15:30:46 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_path(char **env, char *cd)
{
	int		i;
	int		k;
	char	*str;
	char	*str2;
	char	**p;
	char	**cmd;
	int		a;

	a = 0;
	str = get_from_env(env, "PATH");
	p = ft_split_two(str, ':');
	k = -1;
	while (cd[++k])
	{
		if (cd[k] == ' ' && cd[k] != '\v')
			a = 1;
	}
	if (a)
		cmd = ft_split(cd, ' ');
	else
		cmd = ft_split(cd, '\v');
	if (access(cmd[0], X_OK) == 0)
	{
		ft_free(cmd);
		ft_free(p);
		return (cmd[0]);
	}
	if (!cmd)
	{
		ft_putstr_fd("minishell : command not found: ", 2);
		if (cmd[0])
			ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		ft_free(cmd);
		g_glob->exit_status = 127;
		exit(g_glob->exit_status);
	}
	i = -1;
	while (p[++i])
	{
		str2 = ft_strjoin(p[i], cmd[0]);
		if (access(str2, X_OK) == 0)
		{
			ft_free(cmd);
			return (str2);
		}
		free(str2);
	}
	g_glob->exit_status = 127;
	ft_putstr_fd("minishell : command not found: ", 2);
	if (cmd[0])
		ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd("\n", 2);
	ft_free(cmd);
	ft_free(p);
	exit(g_glob->exit_status);
}

void	ft_is_erreur(char **mycmd, char **mypath)
{
	write(2, "command not found : ", 20);
	if (*mycmd)
		write(2, *mycmd, ft_strlen(*mycmd));
	write(2, "\n", 1);
	if (mypath[0])
		ft_freee(mypath, NULL);
	ft_freee(mycmd, NULL);
}
