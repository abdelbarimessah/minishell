/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:29 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/28 16:58:56 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int ac, char **av, char **env)
{
    char *input_str;

    (void)av;
    (void)env;
    if(ac != 1)
        return (printf("program doesnt accepts args !"), 0);
    input_str = NULL;
    while(1)
    {
        input_str = readline("minishell -> ");
        if(!input_str || !ft_strcmp(input_str, "exit"))
            break;
        
        //tokenizer(input_str, env);
        if(!check_syntax(input_str))
            ft_error("syntax error !\n", 0);
        if(input_str[0] != '\0')
            add_history(input_str);
        free(input_str);
    }
    printf("exit\n");
    return (0);
}