/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:01:46 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/25 18:24:57 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_special_caracs(char *str)
{
	char	*special;
	int		i;
	int		j;

	i = 0;
	special = ft_strdup(";#&\\");
	while (str[i])
	{
		j = 0;
		while (special[j])
		{
			if (str[i] == special[j])
				return (0);
			j++;
		}
		if (str[i] == '"' || str[i] == '\'')
		{
			i++;
			while (str[i] && (str[i] != '"' && str[i] != '\''))
				i++;
		}
		i++;
	}
	free(special);
	return (1);
}

int	ft_check_oredi(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] != '>')
		{
			i++;
			while (input[i] && input[i] == ' '
				&& input[i] != '|' && input[i] != '<' && input[i] != '>')
				i++;
			if (!input[i]
				|| input[i] == '|' || input[i] == '<' || input[i] == '>')
				return (print_error_syntax(), 0);
		}
		i++;
	}
	return (1);
}

int	check_syntax(char *str)
{
	if (!check_special_caracs(str))
		return (0);
	if (!ft_check_pipe(str))
		return (0);
	if (!ft_check_input_h(str))
		return (0);
	if (!ft_check_iredi(str))
		return (0);
	if (!ft_check_output_h(str))
		return (0);
	if (!ft_check_oredi(str))
		return (0);
	return (1);
}
