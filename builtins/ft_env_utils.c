/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:18:50 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/21 16:56:29 by ntanjaou         ###   ########.fr       */
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

void	print_sort_list_utils(char *str)
{
	if (check_for_equal(str) != 0)
		ft_putstr_fd("\"\n", 1);
	else
		ft_putstr_fd("\n", 1);
}

void	print_sort_list(t_env *tmp1)
{
	t_env	*tmp;
	int		l;

	l = 0;
	tmp = tmp1;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		l = 0;
		if (!ft_strncmp("OLDPWD", tmp->export_value, 6) && g_glob->index == 0)
		{
			ft_putstr_fd("OLDPWD\n", 1);
			tmp = tmp->next;
			continue ;
		}
		while (tmp->export_value[l])
		{
			if (tmp->export_value[l] == '=' && tmp->export_value[l - 1] != '=')
				l = print_sort_list_utils1(l);
			write(1, &tmp->export_value[l], 1);
			l++;
		}
		print_sort_list_utils(tmp->value);
		tmp = tmp->next;
	}
}

char	*ft_export_utils(char *str)
{
	int		j;
	int		j1;
	char	*plus;

	j = 0;
	j1 = 0;
	plus = malloc(sizeof(char *) * (ft_strlen(str) - 1));
	while (str[j])
	{
		plus[j] = str[j];
		if (str[j] == '+')
			break ;
		j++;
	}
	j1 = j;
	j += 1;
	while (str[j])
	{
		plus[j1] = str[j];
		j++;
		j1++;
	}
	plus[j1] = '\0';
	return (plus);
}
