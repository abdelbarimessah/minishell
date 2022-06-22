/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:39:36 by amessah           #+#    #+#             */
/*   Updated: 2022/06/21 16:54:28 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	swap_list(t_env *a, t_env *b)
{
	char	*str;

	str = a->export_value;
	a->export_value = b->export_value;
	b->export_value = str;
}

t_env	*sort_env(t_env *tmp)
{
	int		swap;
	t_env	*list;

	swap = 1;
	list = tmp;
	while (swap == 1)
	{
		swap = 0;
		while (list != NULL && list->next != NULL)
		{
			if (ft_strcmp(list->export_value, list->next->export_value) > 0
				&& list->export_value != NULL
				&& list->next->export_value != NULL)
			{
				swap_list(list, list->next);
				swap = 1;
			}
			list = list->next;
		}
		list = tmp;
	}
	print_sort_list(list);
	return (tmp);
}

int	check_for_special(char *str)
{
	int	i;

	i = 0;
	if (check_for_equal(str))
	{
		while (str[i])
		{
			if ((str[i] == '+' && str[i + 1] != '=' && str[i - 1] != '=' ))
				return (0);
			i++;
		}
	}
	else
	{
		while (str[i])
		{
			if (!ft_isalnum1(str[i]) && str[i] != '_')
				return (0);
			i++;
		}
	}
	return (1);
}

void	check_args(char **str)
{
	int		i;
	t_env	*tmp;
	char	*ui;

	tmp = g_glob;
	i = 1;
	while (str[i])
	{
		if ((str[i][0] == '_' || ft_isalpha(str[i][0]))
			&& check_for_special(str[i]))
			ft_export_utils1(str[i], tmp);
		else
		{
			ui = ": not a valid identifier\n";
			ft_putstr_3("minishell: export: ", str[i], ui);
			g_glob->exit_status = 1;
		}
		i++;
	}
	ft_free(str);
}

void	ft_export(char **str)
{
	t_env	*list;

	list = g_glob;
	if (!str[1])
		sort_env(list);
	else
		check_args(str);
}
