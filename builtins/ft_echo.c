/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 23:22:42 by amessah           #+#    #+#             */
/*   Updated: 2022/05/28 11:57:23 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == 0)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int ft_check_n(char *str,char *substr)
{
	int i ;
	int j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if(str[i] == substr[j] && str[i + 1] == substr[j + 1])
			return(0);
		i++;
	}
	return (1);
}

int				ft_echo(char **args)
{
	int		i;
	int		n_option;
	int cpt;

	i = 2;
	n_option = 0;
	cpt = 0;
	while (args[i] && ft_check_n(args[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (1);
}