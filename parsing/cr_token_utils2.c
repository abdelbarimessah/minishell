/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_token_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:28:18 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/23 17:31:21 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	herdoc_utils(char *str, t_vars *var)
{
	var->ct_j = 0;
	while (str[var->ct_i] && str[var->ct_i] != '\'' && str[var->ct_i] != '"'
		&& str[var->ct_i] != ' ' && str[var->ct_i] != '<'
		&& str[var->ct_i] != '>' && str[var->ct_i] != '|')
	{
		var->ct_i++;
		var->ct_j++;
	}
	var->ct_sb = ft_substr(str, var->ct_i - var->ct_j, var->ct_j);
	var->ct_limiter = ft_strjoin(var->ct_limiter, var->ct_sb);
}

int	herdoc_utils_2(t_vars *var, char *str)
{
	int	state;

	if (str[var->ct_i] == '"')
	{
		state = herdoc_dquo(str, var);
		if (state)
			var->ct_i = state;
		else
			return (0);
	}
	else if (str[var->ct_i] == '\'')
	{
		state = herdoc_squo(str, var);
		if (state)
			var->ct_i = state;
		else
			return (0);
	}
	return (1);
}

int	herdoc(t_vars *var, char *str, t_list **node)
{
	var->ct_limiter = ft_strdup("");
	var->ct_i += 2;
	ft_lstadd_back(node, ft_lstnew(ft_strdup("<<"), INTPUTE_HEREDOC));
	while (str[var->ct_i] == ' ')
		var->ct_i++;
	while (str[var->ct_i] && str[var->ct_i] != ' '
		&& str[var->ct_i] != '<'
		&& str[var->ct_i] != '>' && str[var->ct_i] != '|')
	{
		if (!herdoc_utils_2(var, str))
			return (0);
		else
			herdoc_utils(str, var);
		free(var->ct_sb);
	}
	ft_lstadd_back(node, ft_lstnew(ft_strdup(var->ct_limiter), LIMITERR));
	free(var->ct_limiter);
	var->ct_j = 5;
	return (1);
}

int	check_sq_dq_p(t_vars *var, t_list **node, char *str)
{
	if (str[var->ct_i] == '|')
		ft_lstadd_back(node, ft_lstnew(ft_strdup("|"), PIP));
	else if (str[var->ct_i] == '"')
	{
		var->ct_j = ft_checker1(node, str, var->ct_i, var->ct_env1);
		if (var->ct_j == -1)
			return (0);
		var->ct_i += var->ct_j + 1;
	}
	else if (str[var->ct_i] == '\'')
	{
		var->ct_j = ft_checker2(node, str, var->ct_i);
		if (var->ct_j == -1)
			return (printf("single quotes not closed !\n"), 0);
		var->ct_i += var->ct_j + 1;
	}
	return (1);
}

int	check_inher_outher(t_vars *var, t_list **node, char *str)
{
	int	state;

	if (str[var->ct_i] == '>' && str[var->ct_i + 1] == '>')
	{
		var->ct_i++;
		ft_lstadd_back(node, ft_lstnew(ft_strdup(">>"), OUTPUTE_HEREDOC));
	}
	else if (str[var->ct_i] == '<' && str[var->ct_i + 1] == '<')
	{
		state = herdoc(var, str, node);
		if (state == 0)
			return (0);
	}
	return (1);
}
