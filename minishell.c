/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:29 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/12 02:26:05 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	printf_list_z(t_env *lst)
{
	while (lst)
	{
		printf("%s\n", lst->value);
		lst = lst->next;
	}
	puts("");
}

int main(int ac, char **av, char **env)
{
    char *input_str;
    char **new_env;
    t_env *list;
    
    (void)av;
    if(ac != 1)
        return (printf("program doesnt accepts args !"), 0);
    input_str = NULL;
    g_glob = list_env(env);
    g_glob->index = 0;
    g_glob->index_env = 0;
    
    signal_handl();
    // rl_catch_signals = 0;
    while(1)
    {
        g_glob->sig = 0;
        list = g_glob;
        new_env = new_env_function(list);
        input_str = readline("minishell ---: ");
        if(!input_str)
            ctrl_d();
        if(!ft_strcmp(input_str, "exit"))
            break;
        if(!check_syntax(input_str))
        {
            ft_error("syntax error ! \n", 0);
            free(input_str);
        }
        else
        {            
            tokenizer(input_str, new_env);
            g_glob->sig = 1;
        }

        g_glob->index++;
        if(input_str[0] != '\0')
            add_history(input_str);
        free(input_str);
    }
    printf("exit\n");
    return (0);
}