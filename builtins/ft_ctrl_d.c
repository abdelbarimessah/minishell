/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 02:27:02 by amessah           #+#    #+#             */
/*   Updated: 2022/06/21 14:01:56 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	ctrl_d(void)
{
	char	*sr_cap;

	sr_cap = tgetstr("sr", NULL);
	tputs(sr_cap, 0, ft_putchar);
	ft_putstr_fd("		exit\n", 1);
	exit(g_glob->exit_status);
}
