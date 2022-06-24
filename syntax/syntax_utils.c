/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:38:33 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/24 17:58:10 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error_syntax(void)
{
	ft_putstr_fd("syntax error !!\n", 2);
}

int	ft_check_pipe(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (!input[i] || input[i] == '|')
				return (print_error_syntax(), 0);
		}
		i++;
	}
	return (1);
}

int	ft_check_input_h(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (input[i] && input[i] == ' ')
				i++;
			if (!input[i]
				|| input[i] == '|' || input[i] == '<' || input[i] == '>')
				return (print_error_syntax(), 0);
		}
		i++;
	}
	return (1);
}

int	ft_check_iredi(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] != '<')
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (!input[i]
				|| input[i] == '|' || input[i] == '<' || input[i] == '>')
				return (print_error_syntax(), 0);
		}
		i++;
	}
	return (1);
}

int	ft_check_output_h(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i] == '>')
		{
			i += 2;
			while (input[i] && input[i] == ' ')
				i++;
			if (!input[i]
				|| input[i] == '|' || input[i] == '<' || input[i] == '>')
				return (print_error_syntax(), 0);
		}
		i++;
	}
	return (1);
}
