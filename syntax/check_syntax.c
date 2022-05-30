/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:01:46 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/30 13:40:07 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_special_caracs(char *str)
{
    char special[] = ";#~&\\";
    int i;
    int j;
    
    i = 0;
    while(str[i])
    {
        j = 0;
        while(special[j])
        {
            if(str[i] == special[j])
                return (0);
            j++;
        }
        if(str[i] == '"' || str[i] == '\'')
        {
            i++;
            while(str[i] && (str[i] != '"' && str[i] != '\''))
                i++;
        }
        i++;
    }
    return (1);
}

int check_double_special_carac(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '|' && str[i + 1] == '|')
            return (0);
        i++;
    }
    return (1);
}

int check_syntax(char *str)
{
    if(!check_special_caracs(str))
        return (0);
    if(!check_double_special_carac(str))
        return (0);
    return (1);
}