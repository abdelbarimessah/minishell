/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:39:36 by amessah           #+#    #+#             */
/*   Updated: 2022/06/18 03:14:47 by amessah          ###   ########.fr       */
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
			if(tmp->export_value[lr] == '=' && tmp->export_value[lr - 1] != '=')
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

int	check_for_special(char *str)
{
	int i;

	i = 0;
	if(check_for_equal(str))
	{
		while(str[i])
		{
			if((str[i] == '+' && str[i + 1] != '=' && str[i - 1] != '=' ))
				return (0);
			i++;
		}
	}
	else
	{
		while (str[i])
		{
			if(!ft_isalnum1(str[i]) && str[i] != '_')
				return(0);
			i++;
		}
	}
	return (1);
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
	int j;
	int j1;
	char *plus;

	cont = 0;
	len = 0;
	j = 0;
	j1 = 0;
	list = g_glob;
	tmp = g_glob;
	i = 1;
	while (str[i])
	{
		if((str[i][0] == '_' || ft_isalpha(str[i][0])) && check_for_special(str[i]))
		{
			while(tmp)
			{
				eq = ft_split(tmp->export_value,'=');
				eq1 = ft_split(str[i],'=');
				len = ft_strlen(eq1[0]);
				if(eq && eq1 &&  !ft_strcmp(eq[0],eq1[0]) && eq1[0][len - 1] != '+'  && eq1[0][len] == '\0' && eq1[1] == NULL)
					cont = 1;
				else if(eq && eq1 &&  !ft_strcmp(eq[0],eq1[0]) && eq1[0][len - 1] != '+' && eq1[1] != NULL)
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
					if(!tmp->export_value[len - 1])
					{
						tmp->export_value = ft_strjoin(tmp->export_value, "=");
						tmp->value = ft_strjoin(tmp->value, "=");
						
					}
					plus = ft_strjoin(tmp->export_value,eq1[1]);
					tmp->export_value = plus;
					tmp->value = plus;
					cont = 1;
					ft_free(eq);
					ft_free(eq1);
					break;
				}
				tmp = tmp->next;
			}
			if(cont == 0)
			{
				if(eq1[0][len - 1 ] == '+')
				{
					cont = 1;
					plus = malloc(sizeof(char *) * (ft_strlen(str[i]) - 1));
					while(str[i][j])
					{
						plus[j] = str[i][j];
						if(str[i][j] == '+')
							break;
						j++;
					}
					j1 = j;
					j += 1;
					while(str[i][j])
					{
						plus[j1] = str[i][j];
						j++;
						j1++;
					}
					plus[j1] = '\0';
				}
				else
					plus = str[i];
				add_to_list(list, plus);
			}
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
		sort_env(list);
	else
		check_args(str);
}