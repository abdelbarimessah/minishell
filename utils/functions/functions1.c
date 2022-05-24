/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:55:46 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/24 12:13:44 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
		return (i);
	}
	return (0);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	rest;
	char	*copie;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	rest = ft_strlen(s) - (size_t)start;
	if (len > rest)
		len = rest;
	copie = malloc(sizeof(char) * (len + 1));
	if (copie == NULL)
		return (NULL);
	while (i < len)
	{
		copie[i] = s[i + start];
		i++;
	}
	copie[i] = '\0';
	return (copie);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] != '\0' || str2[i] != '\0' ) && i < n)
	{
		if (s1[i] != s2[i])
			return ((str1[i] - str2[i]));
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}
