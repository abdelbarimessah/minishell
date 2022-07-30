/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:28:18 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/21 19:03:08 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cmdd(char **cmd)
{
	if (!cmd)
	{
		ft_putstr_fd("minishell : command not found: ", 2);
		if (cmd[0])
			ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		ft_free(cmd);
		g_glob->exit_status = 127;
		return (0);
	}
	return (1);
}

char	**spc_ver(char *cd)
{
	int		k;
	int		i;
	char	**cmd;

	i = 0;
	k = -1;
	while (cd[++k])
	{
		if (cd[k] == ' ' && cd[k] != '\v')
			i = 1;
	}
	if (i)
		cmd = ft_split(cd, ' ');
	else
		cmd = ft_split(cd, '\v');
	return (cmd);
}

void	cmd_notfound(char **cmd)
{
	g_glob->exit_status = 127;
	ft_putstr_fd("minishell : command not found: ", 2);
	if (cmd[0])
		ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd("\n", 2);
	ft_free(cmd);
}

char	*ft_path(char **env, char *cd)
{
	t_vars	var;

	var.pth_i = 0;
	var.pth_str = get_from_env(env, "PATH");
	var.pth_p = ft_split_two(var.pth_str, ':');
	var.pth_cmd = spc_ver(cd);
	if (access(var.pth_cmd[0], X_OK) == 0)
		return (ft_free(var.pth_p), ft_free(var.pth_cmd), cd);
	var.pth_ans = check_cmdd(var.pth_cmd);
	if (!var.pth_ans)
		exit(g_glob->exit_status);
	var.pth_i = -1;
	while (var.pth_p[++var.pth_i])
	{
		var.pth_str2 = ft_strjoin(var.pth_p[var.pth_i], var.pth_cmd[0]);
		if (access(var.pth_str2, X_OK) == 0)
			return (ft_free(var.pth_cmd), var.pth_str2);
		free(var.pth_str2);
	}
	cmd_notfound(var.pth_cmd);
	ft_free(var.pth_p);
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
