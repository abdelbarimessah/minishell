/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:21:54 by amessah           #+#    #+#             */
/*   Updated: 2022/06/21 16:45:19 by ntanjaou         ###   ########.fr       */
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
	int		len;
	char	**eq1;
	char	**eq;
	char	*plus;

	cont  = 0;
	list = g_glob;
	while (tmp)
	{
		eq = ft_split(tmp->export_value, '=');
		eq1 = ft_split(str, '=');
		len = ft_strlen(eq1[0]);
		if (eq && eq1 && !ft_strcmp(eq[0], eq1[0])
		&& eq1[0][len - 1] != '+'
		&& eq1[0][len] == '\0' && eq1[1] == NULL)
		{
			cont = 1;
			break ;
		}
		else if (eq && eq1 && !ft_strcmp(eq[0], eq1[0])
			&& eq1[0][len - 1] != '+' && eq1[1] != NULL)
		{
			free(tmp->export_value);
			free(tmp->value);
			tmp->export_value = ft_strdup(str);
			tmp->value = ft_strdup(str);
			cont = 1;
			ft_free(eq1);
			ft_free(eq);
			break ;
		}
		else if (eq && eq1 && !ft_strncmp(eq[0], eq1[0], len -1)
			&& eq1[0][len - 1] == '+' )
		{
			if (!tmp->export_value[len - 1])
			{
				tmp->export_value = ft_strjoin(tmp->export_value, "=");
				tmp->value = ft_strjoin(tmp->value, "=");
			}
			plus = ft_strjoin(tmp->export_value, eq1[1]);
			tmp->export_value = ft_strdup(plus);
			tmp->value = ft_strdup(plus);
			cont = 1;
			free(plus);
			ft_free(eq);
			ft_free(eq1);
			break ;
		}
			// ft_free(eq);
			// ft_free(eq1);
		tmp = tmp->next;
	}
	if (cont == 0)
	{
		if (eq1[0][len - 1] == '+')
			plus = ft_export_utils(str);
		else
			plus = ft_strdup(str);
		add_to_list(list, plus);
		// free(plus);
	}
}