/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:01:46 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/12 21:17:36 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_error_pipe(t_list *list)
{
    while(list)
    {
        if(list->token == PIP)
        {
            list = list->next;
            while(list->token == SPACE)
                list = list->next;
            if(list->next->token != WORD || list->next->token == END_TOK)
                return (0);
        }
        list = list->next;
    }
    return (1);
}

int check_special_caracs(char *str)
{
    char special[] = ";#&\\";
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

int check_syntax_list(t_list *list)
{
    if(!ft_error_pipe(list))
        return (0);
    return (1);
}