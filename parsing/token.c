/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:23:07 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/24 18:28:27 by ntanjaou         ###   ########.fr       */
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
        else if (str[i] == '<')
            return (simple_redi_left);
        else if (str[i] == '>')
            return (simple_redi_right);
        else
            return (general_word);
    }
    return (0);
}

t_token *create_token(char token_value, t_token_type token_type)
{
    t_token *token;
    int size;

    size = sizeof(t_token);
    token = malloc(size);
    if(!token || !token_value)
        exit(1);
    token->value = token_value;
    token->type = token_type;
    return (token);
}

void tokenizer(char *str)
{
    int i = -1;
    char *value;
    t_list *new;
    t_token *tokeny;
    t_token_type tok_type;

    value = ft_strdup(str);
    if(!value)
        exit(0);
    while(value[++i])
    {
        tok_type = getChartype(&value[i]);
        tokeny = create_token(value[i], tok_type);
        if(!(new = ft_lstnew(tokeny)))
            exit(1);
        ft_lstadd_back(&g_info.list_input_token, new);
    }
}
