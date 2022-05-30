/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:23:07 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/30 14:18:45 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_str(char *str, int i)
{
	if(str[i] && str[i] != '|' && str[i] != '&' && str[i] != ' '
		&& str[i] != '\'' && str[i] != '"'  && str[i] != '$'
		&& str[i] != '(' && str[i] != ')' && str[i] != '>' && str[i] != '<')
		return(1);
	else
	{
		if(str[i] == '&' && str[i + 1] != '&')
			return(1);
		else
			return(0);
	}
}

int check_pipe(t_list *token)
{
    t_list *head;
    head = token;

    while(head)
    {
        if(head->token == PIP)
            return (1);
        head = head->next;
    }
    return (0);
}

int ft_checker1(t_list **node, char *str, int i, char **env)
{
    int j;
    int c;
    int n;
    char *s;
    
    j = i;
    if(str[j] == '"' && str[j + 1] == '"')
        return (0);
    while(str[++j])
    {
        if(str[j] == '"')
            break ;
    }
    if(str[j] == '"')
    {
        i++;
        c = i - 1;
        while(++c < j)
        {
            if(str[c] == '$')
                break;
        }
        if(str[c] == '$')
        {
            ft_lstadd_back(node, ft_lstnew(ft_substr(str, i, c - i), WORD));
            n = c++;
            while(check_str(str, c))
                c++;
            s = get_from_env(env, ft_substr(str, n + 1, c - (n + 1)));
            ft_lstadd_back(node, ft_lstnew(ft_strdup(s), WORD));
            n = c;
            while(c < j)
                c++;
            ft_lstadd_back(node, ft_lstnew(ft_substr(str, n, c - n), WORD));
        }
        else
            ft_lstadd_back(node, ft_lstnew(ft_substr(str, i, j - i), WORD));
        return (j - i + 1);
    }
    return(printf("double quotes not closed !\n"), -1);
}

int ft_checker2(t_list **node, char *str, int i)
{
    int j;

    j = i;
    if(str[j] == '\'' && str[j + 1] == '\'')
        return (0);
    while(str[++j])
    {
        if(str[j] == '\'')
            break ;
    }
    if(str[j] == '\'')
    {
        i++;
        ft_lstadd_back(node, ft_lstnew(ft_substr(str, i, j - i), WORD));
        return (j - i + 1);
    }
    return (-1);
}

int ft_create_tokens(struct s_list **node, char *str, char **env) 
{
    int i;
    int j;
    char *s;

    i = 0;
    j = 1;
    
    while(str[i] == ' ')
        i++;
    while(i < ft_strlen(str))
    {
        j = 0;
        if(str[i] == ' ')
        {
            while(str[i] == ' ')
                i++;
            if(!str[i])
                break;
            ft_lstadd_back(node, ft_lstnew(ft_strdup(" "), SPACE));
            i--;
        }
        else if(str[i] == '|')
            ft_lstadd_back(node, ft_lstnew(ft_strdup("|"), PIP));
        else if(str[i] == '"')
        {
            j = ft_checker1(node, str, i, env);
            if(j == -1)
                return (0);
            i += j + 1;
        }
        else if(str[i] == '\'')
        {
            j = ft_checker2(node, str, i);
            if( j == -1)
            {
                printf("single quotes not closed !\n");
                return 0;
            }
            i += j + 1;
        }
        else if(str[i] == '$')
        {
            if(!str[i + 1] || str[i + 1] == ' ')
                ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WORD));
            else
            {
                j = i + 1;
                while(check_str(str, j))
                    j++;
                s = get_from_env(env, ft_substr(str, i + 1, j - (i + 1)));
                ft_lstadd_back(node, ft_lstnew(ft_strdup(str), WORD));
                i += (j - i);
            }
        }
        else if(str[i] == '>')
            ft_lstadd_back(node, ft_lstnew(ft_strdup(">"), OUTPUTE_REDI));
        else if(str[i] == '<')
            ft_lstadd_back(node, ft_lstnew(ft_strdup("<"), INPUTE_REDI));
        else
        {
            i--;
            while(check_str(str, ++i))
                j++;
            ft_lstadd_back(node, ft_lstnew(ft_substr(str,  i - j, j), WORD));
        }
        if(!j)
            i++;
    }
    ft_lstadd_back(node, ft_lstnew(ft_strdup("<-"), END_TOK));
    
    return (1);
}

void	printf_list(t_list *lst)
{
	while (lst)
	{
		printf("%d - %s\n", lst->token, lst->content);
		lst = lst->next;
	}
	puts("");
}

void ft_join_pipe(t_list *node, char **env)
{
    t_list *head;
    char *str;
    char **str_split;

    (void)env;
    str = ft_strdup("");
    head = node->next;
    while(head->token != END_TOK)
    {
        if(head->token == PIP)
            str = ft_strjoin(str, "|");
        else if(head->token == SPACE)
            str = ft_strjoin(str, " ");
        else
            str = ft_strjoin(str, head->content);
        head = head->next;
    }
    str_split = ft_split(str, '|');
    free(str);
    /// --> work with the pipe
}

void tokenizer(char *str, char  **env)
{
    int i;
    int j;
    t_list *token;
    t_list *head;
    
    i = 0;
    j = 1;
    if(str[0] == '\0')
        return;
    token = ft_lstnew(ft_strdup("->"), START_TOK);
    head = token;
    if(!ft_create_tokens(&token, str, env))
        return ;
    if(check_pipe(head))
       ft_join_pipe(head, env);
    //printf_list(head);
}