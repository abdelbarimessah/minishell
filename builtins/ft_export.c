/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:39:36 by amessah           #+#    #+#             */
/*   Updated: 2022/06/12 02:21:11 by amessah          ###   ########.fr       */
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
		if(check_for_equal(tmp->value) != 0)
		{
			ft_putstr_fd("\"\n",1);
		}
		else
			ft_putstr_fd("\n",1);
		tmp = tmp->next;
	}
	return (tmp);
}

void	check_args(char **str)
{
	int i;
	t_env *list;
	t_env *tmp;
	char **eq;
	char **eq1;
	int cont;
	int len;

	cont = 0;
	len = 0;
	list = g_glob;
	tmp = g_glob;
	i = 1;
	while (str[i])
	{
		if(str[i][0] == '-' || ft_isalpha(str[i][0]))
		{
			while(tmp)
			{
				eq = ft_split(tmp->export_value,'=');
				eq1 = ft_split(str[i],'=');
				len = ft_strlen(eq1[0]);
				if(eq && eq1 &&  !ft_strcmp(eq[0],eq1[0]) && eq1[0][len - 1] != '+')
				{
					tmp->export_value = str[i];
					tmp->value  = str[i];
					cont = 1;
					ft_free(eq);
					ft_free(eq1);
					break;
				}
				else if(eq && eq1 && !ft_strncmp(eq[0],eq1[0],len -1) && eq1[0][len - 1 ] == '+')
				{
					tmp->export_value = ft_strjoin(tmp->export_value,eq1[1]);
					tmp->value = ft_strjoin(tmp->export_value,eq1[1]);
					cont = 1;
					ft_free(eq);
					ft_free(eq1);
					break;
				}
				tmp = tmp->next;
			}
			if(cont == 0)
				add_to_list(list, str[i]);
		}
		else
		{
			ft_putstr_fd("minishell: export: ",2);
			ft_putstr_fd(str[i],2);
			ft_putstr_fd(": not a valid identifier\n",2);
			g_glob->exit_status = 1;
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