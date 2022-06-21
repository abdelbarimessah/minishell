/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:18:50 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/21 15:52:47 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*search_and_replce_oldpwd(t_env *list, void *data)
{
	if (!list || !data)
		return (NULL);
	while (list)
	{
		if (!ft_strncmp(list->value, "OLDPWD", 6))
		{
			list->value = data;
		}
		list = list->next;
	}
	return (list);
}

t_env	*search_and_replce_pwd(t_env *list, void *data)
{
	if (!list || !data)
		return (NULL);
	while (list)
	{
		if (!ft_strncmp(list->value, "PWD", 3))
		{
			list->value = data;
		}
		list = list->next;
	}
	return (list);
}

void	print_sort_list(t_env *tmp1)
{
	t_env	*tmp;
	int		lr;

	lr = 0;
	tmp = tmp1;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		lr = 0;
		while (tmp->export_value[lr])
		{
			if (tmp->export_value[lr] == '='
				&& tmp->export_value[lr - 1] != '=')
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd("\"", 1);
				lr++;
			}
			write(1, &tmp->export_value[lr], 1);
			lr++;
		}
		if (check_for_equal(tmp->value) != 0)
		{
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}
