/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:29 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/05/24 15:06:33 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int ac, char **av, char **env)
{
    char *input_str;
    size_t len_str;

    int i = -1;
    g_info.path = get_path(env);
    g_info.info_env = malloc(1000);
    while(env[++i])
        g_info.info_env[i] = env[i];
    (void)av;
    if(ac != 1)
        return (printf("program doesnt accepts args !"), 0);
    input_str = NULL;
    while(1)
    {
        input_str = readline("minishell -> ");
        len_str = ft_strlen(input_str);
        if(!input_str || !ft_strcmp(input_str, "exit"))
            break;
        
        //lexer
       
     
        printf("%d\n", getChartype(input_str));
        if(input_str[0] != '\0')
            add_history(input_str);
        free(input_str);
    }
    printf("exit\n");
    return (0);
}