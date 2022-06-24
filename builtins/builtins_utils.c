/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:30:27 by amessah           #+#    #+#             */
/*   Updated: 2022/06/24 20:15:12 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	r;
	int	s;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\f'
		||str[i] == '\v' || str[i] == '\r')
		i++;
	if (str[i] == '-' )
		s = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - '0');
		i++;
	}
	return (r * s);
}

char	**new_env_function(t_env *list)
{
	char	**env;
	int		i;

	i = 0;
	env = malloc(10000);
	if (!list)
		return (NULL);
	while (list)
	{
		env[i] = list->value;
		list = list->next;
		i++;
	}
	return (env);
}

int	ft_cd_utils(char **args, int a)
{
	if (g_glob->index == 0)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	else
	{
		args[1] = path_oldpwd(g_glob);
		if (chdir(args[1]) == -1)
		{
			ft_putstr_fd("cd: ", 1);
			ft_putstr_fd(args[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
	a++;
	return (a);
}

void	ft_putstr_3(char *str, char *str1, char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
}

char	*ft_cd_home(t_env *list, char **args)
{
	char	*str;
	char	**cm;

	cm = new_env_function(list);
	str = check_home_path(cm);
	if (!str)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_glob->exit_status = 1;
		return (NULL);
	}
	args[1] = ft_strcpy(str);
	free(str);
	g_glob->index++;
	return (args[1]);
}
