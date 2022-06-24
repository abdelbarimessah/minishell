/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:41:58 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/24 22:35:42 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	last_tok(t_vars *var, char *str, t_list **node)
{
	if (str[var->ct_i] != ' ')
	{
		var->ct_i--;
		while (check_str(str, ++var->ct_i))
			var->ct_j++;
		ft_lstadd_back(node, ft_lstnew
			(ft_substr(str, var->ct_i - var->ct_j, var->ct_j), WORD));
	}
}

void	redi_in_out(t_vars *var, char *str, t_list **node)
{
	if (str[var->ct_i] == '<' && str[var->ct_i + 1] != '<')
		ft_lstadd_back(node, ft_lstnew(ft_strdup("<"), INPUTE_REDI));
	else if (str[var->ct_i] == '>' && str[var->ct_i + 1] != '>')
		ft_lstadd_back(node, ft_lstnew(ft_strdup("<"), OUTPUTE_REDI));
}

int	token_cr_ut(t_vars *var, t_list **node, char *str)
{
	int	state;

	var->ct_j = 0;
	if (str[var->ct_i] == ' ')
	{
		if (!spc_tok(str, node, var))
			return (2);
		return (3);
	}	
	else if (str[var->ct_i] == '"' || str[var->ct_i] == '\''
		|| str[var->ct_i] == '|')
	{
		state = check_sq_dq_p(var, node, str);
		if (!state)
			return (0);
		return (3);
	}
	return (1);
}

int	token_cr(t_vars *var, t_list **node, char *str)
{
	int	state;

	state = token_cr_ut(var, node, str);
	if (state != 1)
	{
		if (state == 3)
			var->ct_i++;
		return (state);
	}
	else if (str[var->ct_i] == '$')
		var->ct_i = dol_tok(str, node, var);
	else if ((str[var->ct_i] == '>' && str[var->ct_i + 1] == '>')
		|| (str[var->ct_i] == '<' && str[var->ct_i + 1] == '<'))
	{
		if (!check_inher_outher(var, node, str))
			return (0);
	}
	else if ((str[var->ct_i] == '>' && str[var->ct_i + 1] != '>')
		|| (str[var->ct_i] == '<' && str[var->ct_i + 1] != '<'))
		redi_in_out(var, str, node);
	else
		last_tok(var, str, node);
	if (!var->ct_j)
		var->ct_i++;
	return (1);
}

int	ft_create_tokens(struct s_list **node, char *str)
{
	t_vars	var;
	int		state;

	init_vars(&var, str);
	while (var.ct_i < ft_strlen(str))
	{
		state = token_cr(&var, node, str);
		if (!state)
			return (0);
		else if (state == 2)
			break ;
	}
	ft_lstadd_back(node, ft_lstnew(ft_strdup("---"), END_TOK));
	return (1);
}
