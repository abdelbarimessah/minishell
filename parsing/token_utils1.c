/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:40:15 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/21 21:05:15 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isalphaa(int c)
{
	if ((c >= 'A' && c <= 'Z' ) || (c >= 'a' && c <= 'z' ))
		return (1);
	else
		return (0);
}

int	ft_isdigitt(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	check_str(char *str, int i)
{
	if (str[i] && str[i] != '|' && str[i] != '&' && str[i] != ' '
		&& str[i] != '\'' && str[i] != '"' && str[i] != '$'
		&& str[i] != '(' && str[i] != ')' && str[i] != '>' && str[i] != '<')
		return (1);
	else
	{
		if (str[i] == '&' && str[i + 1] != '&')
			return (1);
		else
			return (0);
	}
}

int	check_tok(t_list *token, int tok)
{
	t_list	*head;

	head = token;
	while (head)
	{
		if (head->token == tok)
			return (1);
		head = head->next;
	}
	return (0);
}

int	check_tok_pip(t_list *token, int tok)
{
	t_list	*head;

	head = token;
	while (head)
	{
		if (head->token == PIP)
			break ;
		if (head->token == tok)
			return (1);
		head = head->next;
	}
	return (0);
}
