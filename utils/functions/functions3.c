/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:25:43 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/25 01:44:12 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen(char *s)
{	
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*copie;
	char	*src1;

	src1 = (char *)src;
	i = 0;
	copie = malloc(sizeof(char) * (ft_strlen(src1) + 1));
	if (!(src) || (copie == NULL))
		return (NULL);
	while (src1[i] != '\0')
	{
		copie[i] = src1[i];
		i++;
	}
	copie[i] = '\0';
	return (copie);
}

int	ft_skip_space(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int	ft_error(char *str, int retu)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (retu);
}

char	*ft_strchr(const char *str, int pos)
{
	int		i;
	char	*str1;
	char	c1;

	str1 = (char *)str;
	c1 = (char)pos;
	i = 0;
	if (c1 == '\0')
		return (str1 + ft_strlen(str1));
	while (str1[i] != '\0')
	{
		if (str1[i] == c1)
			return (str1 + i);
		i++;
	}
	return (NULL);
}
