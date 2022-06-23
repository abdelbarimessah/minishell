/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:09 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/23 21:30:12 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_exec(t_vars *var)
{
	var->fdd[0] = dup(0);
	var->fdd[1] = dup(1);
	var->crt_str = ft_strdup("");
}

int	inp_redi_exec(t_list **node, t_vars *var)
{
	var->crt_file_n = ft_strdup("");
	(*node) = (*node)->next;
	if ((*node)->token == WSPACE)
		(*node) = (*node)->next;
	while ((*node)->token == WORD && (*node)->token != END_TOK)
	{
		var->crt_file_n = ft_strjoin(var->crt_file_n, (*node)->content);
		(*node) = (*node)->next;
	}
	var->fdd[0] = open(var->crt_file_n, O_RDONLY);
	if (var->fdd[0] == -1)
	{
		printf(" ---> %s <----- No such file or directory\n", var->crt_file_n);
		return (0);
	}
	free(var->crt_file_n);
	return (var->fdd[0]);
}

void	inp_herdc_exec(t_list **node, t_vars *var)
{
	var->value = ft_strdup("");
	(*node) = (*node)->next;
	while ((*node)->token == WSPACE && (*node)->token != END_TOK)
		(*node) = (*node)->next;
	while (1)
	{
		var->crt_p = readline("> ");
		if (!ft_strcmp_2(var->crt_p, (*node)->content))
			break ;
		var->crt_p = ft_strjoin_nf(var->crt_p, "\n");
		var->value = ft_strjoin(var->value, var->crt_p);
		free(var->crt_p);
	}
}

int	outp_redi_exec(t_list **node, t_vars *var)
{
	var->crt_file_n = ft_strdup("");
	(*node) = (*node)->next;
	if ((*node)->token == WSPACE)
		(*node) = (*node)->next;
	while ((*node)->token == WORD && (*node)->token != END_TOK)
	{
		var->crt_file_n = ft_strjoin(var->crt_file_n, (*node)->content);
		(*node) = (*node)->next;
	}
	var->fdd[1] = open(var->crt_file_n, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (var->fdd[1] == -1)
	{
		printf(" %s Error in file creation\n", var->crt_file_n);
		return (0);
	}
	free(var->crt_file_n);
	return (var->fdd[1]);
}

int	outp_herdc_exec(t_list **node, t_vars *var)
{
	var->crt_file_n = ft_strdup("");
	(*node) = (*node)->next;
	if ((*node)->token == WSPACE)
		(*node) = (*node)->next;
	while ((*node)->token == WORD && (*node)->token != END_TOK)
	{
		var->crt_file_n = ft_strjoin(var->crt_file_n, (*node)->content);
		(*node) = (*node)->next;
	}
	var->fdd[1] = open(var->crt_file_n, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (var->fdd[1] == -1)
	{
		printf(" %s Error in file creation\n", var->crt_file_n);
		return (0);
	}
	free(var->crt_file_n);
	return (var->fdd[1]);
}
