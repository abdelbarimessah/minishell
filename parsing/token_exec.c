/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:30:04 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/25 19:02:41 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	out_herdc_redi_exec(t_list **node, t_vars *var)
{
	if ((*node)->token == OUTPUTE_HEREDOC)
	{
		var->fdd[1] = outp_herdc_exec(&(*node), var);
		if (!var->fdd[1])
			return (0);
	}
	else if ((*node)->token == OUTPUTE_REDI)
	{
		var->fdd[1] = outp_redi_exec(&(*node), var);
		if (!var->fdd[1])
			return (0);
	}
	return (var->fdd[1]);
}

void	spc_null_word(t_list **node, t_vars *var)
{
	if ((*node)->token == WSPACE)
		var->crt_str = ft_strjoin2(var->crt_str, "\v");
	else if ((*node)->token == NUL)
		var->crt_str = ft_strjoin2(var->crt_str, " ");
	else if ((*node)->token == WORD)
		var->crt_str = ft_strjoin2(var->crt_str, (*node)->content);
}

void	loop_lst_exec(t_list **node, t_vars *var)
{
	while ((*node))
	{
		if ((*node)->token == WSPACE
			|| (*node)->token == NUL || (*node)->token == WORD)
			spc_null_word(&(*node), var);
		else if ((*node)->token == INPUTE_REDI)
		{	
			var->fdd[0] = inp_redi_exec(&(*node), var);
			if (!var->fdd[0])
				break ;
			var->z[0] = 0;
		}
		else if ((*node)->token == INTPUTE_HEREDOC)
			inp_herdc_exec(&(*node), var);
		else if ((*node)->token == OUTPUTE_HEREDOC
			|| (*node)->token == OUTPUTE_REDI)
		{
			var->fdd[1] = out_herdc_redi_exec(&(*node), var);
			if (!var->fdd[1])
				break ;
			var->z[1] = 1;
		}
		(*node) = (*node)->next;
	}
}

void	ft_execute_comnd(t_list *node, char **env)
{
	t_list	*head;
	t_vars	var;

	(void)env;
	init_exec(&var);
	head = node;
	head = head->next;
	loop_lst_exec(&head, &var);
	var.crt_cmd = ft_split(var.crt_str, '\v');
	if (!var.crt_cmd[0] || !var.crt_str[0])
		return ;
	else
	{
		var.crt_pid = fork();
		g_glob->g_pid = var.crt_pid;
		if (var.crt_pid == 0)
			execute_tb(var.crt_str, env, node, var);
		else
			g_glob->status = 1;
		waitpid(var.crt_pid, &var.crt_wait_int, 0);
		status_child(var.crt_wait_int);
	}
	ft_free(var.crt_cmd);
	free(var.crt_str);
}
