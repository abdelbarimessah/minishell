/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:32:13 by amessah           #+#    #+#             */
/*   Updated: 2022/06/24 20:22:49 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isalpha(int c)
{
	if ((c > 'Z' && c < 'a') || c > 'z' || c < 'A')
	{
		return (0);
	}
	return (1);
}

int	ft_isalnum1(int c)
{
	if (c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z')
		return (0);
	return (1);
}

void	deletenode_from_env(t_env *list, char *str, int len)
{
	t_env	*tmp;
	t_env	*head;
	int		cont;

	head = g_glob;
	cont = 0;
	while (head)
	{
		if (!ft_strncmp(head->value, str, len))
			cont++;
		head = head->next;
	}
	if (cont != 0)
	{
		while (list)
		{
			tmp = list->next;
			if (!ft_strncmp(tmp->value, str, len))
				break ;
			list = list->next;
		}
		if (tmp && list)
			list->next = tmp->next;
	}
}

int	check_arg(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	if (ft_isalpha(arg[i]) || arg[i] == '_')
	{
		while (arg[++i])
			if (!(ft_isalnum1(arg[i]) || arg[i] == '_'))
				return (0);
		return (1);
	}
	return (0);
}

void	ft_unset(char **str)
{
	int		i;
	t_env	*list;
	t_env	*tmp;
	int		len;

	list = g_glob;
	tmp = g_glob;
	i = 1;
	len = 0;
	while (str[i])
	{
		if (!check_arg(str[i]))
		{
			ft_putstr_3("unset: `", str[i], "': not a valid identifier\n");
			g_glob->exit_status = 1;
		}
		else
		{
			len = ft_strlen(str[i]);
			deletenode_from_env(list, str[i], len);
		}
		i++;
	}
	ft_free(str);
}
