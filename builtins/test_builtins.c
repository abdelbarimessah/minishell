/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:21:54 by amessah           #+#    #+#             */
/*   Updated: 2022/06/23 16:46:59 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_test_builtins(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd);
}

void	test_builtins(t_list *node, char **env)
{
	t_list	*head;
	char	*str;
	char	**cmd;
	int		c;

	(void)env;
	str = ft_strdup("");
	head = node->next;
	c = 0;
	while (head->token != END_TOK)
	{
		if (head->token == WSPACE)
			str = ft_strjoin(str, "\v");
		else if (head->content)
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	cmd = ft_split(str, '\v');
	check_test_builtins(cmd);
}

int	print_sort_list_utils1(int lr)
{
	ft_putstr_fd("=\"", 1);
	lr++;
	return (lr);
}

void	ft_export_utils1(char *str, t_env *tmp)
{
	t_env	*list;
	int		cont;
	char	**eq1;
	char	**eq;

	cont = 0;
	list = g_glob;
	while (tmp)
	{
		eq = ft_split(tmp->export_value, '=');
		eq1 = ft_split(str, '=');
		if (!ft_export_utils4(eq, eq1))
			cont = 1;
		else if (!ft_export_utils5(eq, eq1))
			cont = ft_export_utils8(tmp, eq, eq1, str);
		else if (!ft_export_utils6(eq, eq1))
			cont = ft_export_utils7(tmp, eq, eq1);
		tmp = tmp->next;
	}
	if (cont == 0)
		ft_export_utils2(eq1, ft_strlen(eq1[0]), str);
}

void	ft_export_utils2(char **eq1, int len, char *str)
{
	t_env	*list;
	char	*plus;

	list = g_glob;
	if (eq1[0][len - 1] == '+')
		plus = ft_export_utils(str);
	else
		plus = ft_strdup(str);
	add_to_list(list, plus);
}
