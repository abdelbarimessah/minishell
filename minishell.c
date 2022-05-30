/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:29 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/30 15:10:59 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int ac, char **av, char **env)
{
    char *input_str;

    (void)av;
    if(ac != 1)
        return (printf("program doesnt accepts args !"), 0);
    input_str = NULL;
    while(1)
    {
        input_str = readline("minishell -> ");
        if(!input_str || !ft_strcmp(input_str, "exit"))
            break;
        
        if(!check_syntax(input_str))
        {
            ft_error("syntax error ! \n", 0);
            free(input_str);
        }
        else
        {
            // tokenizer(input_str, env);
            test_builtins(input_str, env);
        }
        if(input_str[0] != '\0')
            add_history(input_str);
        free(input_str);
    }
    printf("exit\n");
    return (0);
}