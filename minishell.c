/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:29 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/31 00:13:13 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int ac, char **av, char **env)
{
    char *input_str;
    t_env *list;
    char **new_env;
    

    (void)av;
    if(ac != 1)
        return (printf("program doesnt accepts args !"), 0);
    input_str = NULL;
    list = list_env(env);
    new_env = new_env_function(list);
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
            //test_builtins(input_str, env);
            tokenizer(input_str, new_env);
        }
        if(input_str[0] != '\0')
            add_history(input_str);
        free(input_str);
    }
    printf("exit\n");
    return (0);
}