/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:53:23 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/22 23:34:54 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_dquo(char *s, int i)
{
	while (s[++i])
	{
		if (s[i] == '"')
			break ;
	}
	return (i);
}

void	init_vars(t_vars *var, char *str)
{
	t_env	*tmp;

	var->ct_i = 0;
	var->ct_j = 1;
	tmp = g_glob;
	var->ct_env1 = new_env_function(tmp);
	while (str[var->ct_i] == ' ')
		var->ct_i++;
}
