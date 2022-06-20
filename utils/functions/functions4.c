/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:27:20 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/20 15:30:31 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlcpy(char *dest, char *src, int size)
{
	int	x;
	int	i;

	x = 0;
	while (src[x] != '\0')
	{
		x++;
	}
	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (x);
}

static	int	ft_len(int n)
{
	int	a;
	int	len;

	a = n;
	len = 0;
	if (a <= 0)
		len++;
	while (a != 0)
	{
		a = a / 10;
		len++;
	}
	return (len);
}

static char	*ft_pos(int n)
{
	char	*p;
	int		a;
	int		len;

	a = n;
	len = ft_len(n);
	p = (char *) malloc (len + 1);
	if (p == NULL)
		return (NULL);
	if (n == 0)
		p[0] = '0';
	while (n != 0)
	{
		len--;
		p[len] = (n % 10) + '0';
		n = n / 10;
	}
	p[ft_len(a)] = '\0';
	return (p);
}

static char	*ft_nega(int n)
{
	char	*p;
	int		a;
	int		len;

	a = n;
	len = ft_len(n);
	p = (char *) malloc (len + 1);
	if (p == NULL)
		return (NULL);
	p[0] = '-';
	if (n == 0)
		p[0] = '0';
	while (n != 0)
	{
		len--;
		p[len] = -(n % 10) + '0';
		n = n / 10;
	}
	p[ft_len(a)] = '\0';
	return (p);
}

char	*ft_itoa(int n)
{
	if (n < 0)
		return (ft_nega(n));
	else
		return (ft_pos(n));
}
