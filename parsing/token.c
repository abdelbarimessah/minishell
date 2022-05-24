/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:23:07 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/24 15:07:19 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int Bad_characters(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == ';' || str[i] == '&' || (str[i] == '|' && str[i + 1] == '|'))
            return 0;
        i++;
    }
    return (1);
}

int getChartype(char *str)
{
    int i = -1;

    if(!Bad_characters(str))
        return (0);
    while(str[++i])
    {
        if (str[i] == '|')
            return(pip);
        else if (str[i] == '\'')
            return (single_quote);
        else if (str[i] == '\"')
            return (double_quote);
        else if (str[i] == ' ')
            return (white_space);
        else if (str[i] == '$')
            return (dollar);
        else if (str[i] == '<' && str[i + 1] != '<')
            return (simple_redi_left);
        else if (str[i] == '>' && str[i + 1] != '>')
            return (simple_redi_right);
        else if (str[i] == '>' && str[i + 1] == '>')
            return (double_redi_right);
        else if (str[i] == '<' && str[i + 1] == '<')
            return (double_redi_left);
    }
    return (general_word);
}
