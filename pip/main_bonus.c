/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:51:04 by amessah           #+#    #+#             */
/*   Updated: 2022/05/31 19:05:25 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(char *argv, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		// free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		// free(path);
		i++;
	}
	i = -1;
	// while (paths[++i])
	// 	free(paths[i]);
	// free(paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	int		i;
	char	**cmd;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		// while (cmd[++i])
		// 	free(cmd[i]);
		// free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}

int	main_pipe(int num_com, char **str, char **env, t_list *node)
{
	int i;
	
	(void)node;
	i = -1;
	while (i < num_com - 1)
		child_process(str[i++], env);
		// dup2(f1, STDOUT_FILENO);
	execute(str[num_com - 1], env);
	return (0);
}