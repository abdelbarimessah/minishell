/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:39:36 by amessah           #+#    #+#             */
/*   Updated: 2022/06/08 17:45:57 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void swap_list(t_env *a,t_env *b)
{
	char *str;
	str = a->export_value;
	a->export_value = b->export_value;
	b->export_value = str;
}



t_env *sort_env(t_env *tmp)
{
	int swap;
	t_env *list;
	int lr;

	swap = 1;
	list = tmp;
	lr = 0;
	while(swap == 1)
	{
		swap = 0;
			list = list->next;
		while(list != NULL && list->next != NULL)
		{
			lr = ft_strcmp(list->export_value,list->next->export_value);
			if(lr > 0 && list->export_value != NULL && list->next->export_value != NULL)
			{
				swap_list(list,list->next);
				swap = 1;
				lr = 0;
			}
			list = list->next;
		}
		list = tmp;
	}
	tmp = tmp->next;
	lr = 0;
	while(tmp)
	{
		ft_putstr_fd("declare -x ",1);
		lr = 0;
		while(tmp->export_value[lr])
		{
			if(tmp->export_value[lr] == '=')
			{
				ft_putstr_fd("=",1);
				ft_putstr_fd("\"",1);
				lr++;
			}
			write(1,&tmp->export_value[lr],1);
			lr++;
		}
		if(check_for_equal(tmp->value) == 0)
		{
			ft_putstr_fd("\n",1);
		}
		else
			ft_putstr_fd("\"\n",1);
		tmp = tmp->next;
	}
	return (tmp);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z' ) || (c >= 'a' && c <= 'z' ))
		return (1);
	else
		return (0);
}

void	check_args(char **str)
{
	int i;
	t_env *list;

	list = g_glob;
	i = 1;
	while (str[i])
	{
		if(str[i][0] == '-' || ft_isalpha(str[i][0]))
		{
			add_to_list(list, str[i]);
			// add_to_list(g_glob, str[i]);
			
		}
		else
		{
			ft_putstr_fd("minishell: export: ",2);
			ft_putstr_fd(str[i],2);
			ft_putstr_fd(": not a valid identifier\n",2);
		}
		i++;
	}
	
}

void    ft_export(char **str)
{
	t_env *list;
	list = g_glob;

	if(!str[1])
	{
		sort_env(list);
	}
	else
	{
		check_args(str);
	}
}