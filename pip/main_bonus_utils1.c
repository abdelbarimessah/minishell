/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:28:16 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/22 16:32:35 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	outp_redi(t_list **nod, t_vars var)
{
	var.file_n = ft_strdup("");
	(*nod) = (*nod)->next;
	if ((*nod)->token == WSPACE)
		(*nod) = (*nod)->next;
	while ((*nod)->token == WORD && (*nod)->token != END_TOK)
	{
		var.file_n = ft_strjoin(var.file_n, (*nod)->content);
		(*nod) = (*nod)->next;
	}
	var.fd[1] = open(var.file_n, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (var.fd[1] == -1)
	{
		printf(" %s Error in file creation\n", var.file_n);
		return (0);
	}
	free(var.file_n);
	return (var.fd[1]);
}

int	outp_herdc(t_list **nod, t_vars var)
{
	var.file_n = ft_strdup("");
	(*nod) = (*nod)->next;
	if ((*nod)->token == WSPACE)
		(*nod) = (*nod)->next;
	while ((*nod)->token == WORD && (*nod)->token != END_TOK)
	{
		var.file_n = ft_strjoin(var.file_n, (*nod)->content);
		(*nod) = (*nod)->next;
	}
	var.fd[1] = open(var.file_n, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (var.fd[1] == -1)
	{
		printf(" %s Error in file creation\n", var.file_n);
		return (0);
	}
	free(var.file_n);
	return (var.fd[1]);
}

int	inp_redi(t_list **nod, t_vars var)
{
	var.file_n = ft_strdup("");
	(*nod) = (*nod)->next;
	if ((*nod)->token == WSPACE)
		(*nod) = (*nod)->next;
	while ((*nod)->token == WORD && (*nod)->token != END_TOK)
	{
		var.file_n = ft_strjoin(var.file_n, (*nod)->content);
		(*nod) = (*nod)->next;
	}
	var.fd[0] = open(var.file_n, O_RDONLY);
	if (var.fd[0] == -1)
	{
		printf(" %s Error in file creation\n", var.file_n);
		return (0);
	}
	free(var.file_n);
	return (var.fd[0]);
}

void	her_dc(t_list **nod, t_vars *var)
{
	char	*p;

	var->value = ft_strdup("");
	(*nod) = (*nod)->next;
	while ((*nod)->token == WSPACE && (*nod)->token != END_TOK)
		(*nod) = (*nod)->next;
	dup2(var->st_in, 0);
	while (1)
	{
		p = readline("> ");
		if (!ft_strcmp(p, (*nod)->content))
			break ;
		p = ft_strjoin_nf(p, "\n");
		var->value = ft_strjoin(var->value, p);
		free(p);
	}
}

void	loop_list(t_list **nod, t_vars *var)
{
	while ((*nod) && (*nod)->token != PIP)
	{
		if ((*nod)->token == OUTPUTE_REDI)
		{
			var->fd[1] = outp_redi(&(*nod), *var);
			if (!var->fd[1])
				break ;
		}
		else if ((*nod)->token == OUTPUTE_HEREDOC)
		{
			var->fd[1] = outp_herdc(&(*nod), *var);
			if (!var->fd[1])
				break ;
		}
		else if ((*nod)->token == INTPUTE_HEREDOC)
			her_dc(&(*nod), var);
		else if ((*nod)->token == INPUTE_REDI)
		{
			var->fd[0] = inp_redi(&(*nod), *var);
			if (!var->fd[0])
				break ;
		}
		else
			(*nod) = (*nod)->next;
	}
}
