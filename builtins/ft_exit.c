/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:11:22 by amessah           #+#    #+#             */
/*   Updated: 2022/05/28 16:01:41 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
int ft_exit(char **str,int nb)
{
	int exit_nb;

	exit_nb = 0;
	if(nb == 2)
	{
		ft_putstr_fd("exit\n",1);
		exit(exit_nb);
	}
	else
	{
		if(ft_isalnum(str[2]) == 0)
		{
			ft_putstr_fd("exit\nexit: ",2);
			ft_putstr_fd(str[2],2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_nb = 255;
		}
		else
		{
			ft_putstr_fd("exit\n",1);
			exit_nb = ft_atoi(str[2]);
		}
		exit(exit_nb);
	}
	return (0);
}