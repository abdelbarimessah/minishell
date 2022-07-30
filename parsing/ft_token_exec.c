/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 22:53:16 by amessah           #+#    #+#             */
/*   Updated: 2022/06/25 23:09:25 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_in(t_vars *var)
{
	dup2(var->fdd[0], var->z[0]);
	close(var->fdd[0]);
}

void	dup_out(t_vars *var)
{
	dup2(var->fdd[1], var->z[1]);
	close(var->fdd[1]);
}

void	ft_pereor(void)
{
	perror("Error");
	exit (1);
}

int	check_toorder(t_vars *var, t_list **node)
{
	if (!ft_is_last((*node), INTPUTE_HEREDOC, INPUTE_REDI, END_TOK))
	{
		dup2(var->fdd[0], var->z[0]);
		close(var->fdd[0]);
	}
	else
	{
		if (pipe(var->jp_end_p) == -1)
			perror("error");
		ft_putstr_fd(var->value, var->jp_end_p[1]);
		close(var->jp_end_p[1]);
		dup2(var->jp_end_p[0], 0);
		close(var->jp_end_p[0]);
	}
	return (1);
}
