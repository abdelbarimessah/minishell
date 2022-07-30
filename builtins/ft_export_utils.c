/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 01:29:18 by amessah           #+#    #+#             */
/*   Updated: 2022/06/23 01:34:32 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_export_utils4(char **eq, char **eq1)
{
	int	len;

	len = ft_strlen(eq1[0]);
	if (eq && eq1 && !ft_strcmp(eq[0], eq1[0])
		&& eq1[0][len - 1] != '+'
		&& eq1[0][len] == '\0' && eq1[1] == NULL)
		return (0);
	return (1);
}

int	ft_export_utils5(char **eq, char **eq1)
{
	int	len;

	len = ft_strlen(eq1[0]);
	if (eq && eq1 && !ft_strcmp(eq[0], eq1[0])
		&& eq1[0][len - 1] != '+' && eq1[1] != NULL)
		return (0);
	return (1);
}

int	ft_export_utils6(char **eq, char **eq1)
{
	int	len;

	len = ft_strlen(eq1[0]);
	if (eq && eq1 && !ft_strncmp(eq[0], eq1[0], len -1)
		&& eq1[0][len - 1] == '+')
		return (0);
	return (1);
}

int	ft_export_utils7(t_env *tmp, char **eq, char **eq1)
{
	char	*plus;

	if (!tmp->export_value[ft_strlen(eq1[0]) - 1])
	{
		tmp->export_value = ft_strjoin(tmp->export_value, "=");
		tmp->value = ft_strjoin(tmp->value, "=");
	}
	plus = ft_strjoin(tmp->export_value, eq1[1]);
	tmp->export_value = ft_strdup(plus);
	tmp->value = ft_strdup(plus);
	free(plus);
	ft_free(eq);
	ft_free(eq1);
	return (1);
}

int	ft_export_utils8(t_env *tmp, char **eq, char **eq1, char *str)
{
	free(tmp->export_value);
	free(tmp->value);
	tmp->export_value = ft_strdup(str);
	tmp->value = ft_strdup(str);
	ft_free(eq1);
	ft_free(eq);
	return (1);
}
