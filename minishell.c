/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:42:29 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/15 01:37:43 by amessah          ###   ########.fr       */
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

// void    incrument_shlvl(void)
// {
//     t_env *tmp;
//     char **str;
//     int shlvl;
//     char *join;

//     tmp = g_glob;
//     while(tmp)
//     {
//         if(!ft_strncmp(tmp->value, "SHLVL", 5))
//         {
//             str = ft_split(tmp->value, '=');
//             shlvl = ft_atoi(str[1]);
//             printf("%d\n",shlvl);
//             shlvl++;
//             join = ft_strjoin("SHLVL=", ft_itoa(shlvl));
//             printf("%s\n",join);
//             tmp->value = join;
//             // printf("%s\n", tmp->value);
//             free(join);
//             ft_free(str);
//             break ;
//         }
//         tmp = tmp->next;
//     }
//     tmp = g_glob;
//     while(tmp){
//         printf("%s\n",tmp->value);
//         tmp  = tmp->next;
//     }
// }

char    *get_shlvl(void)
{
    t_env *list;
    char *str;
    char **num;

    list = g_glob;
    while(list)
    {
        if(!ft_strncmp(list->value,"SHLVL",5))
        {
            str = list->value;
            break;
        }
        list = list->next;
    }
    num = ft_split(str, '=');
    return (num[1]);
}

void    incrument_shlvl(void)
{
    char **str;
    
    g_glob->shlvl_val = ft_atoi(get_shlvl());
    g_glob->shlvl_val++;
    str = malloc(100000);////******************************
    str[0] = ft_strdup("export");
    str[1] = ft_strjoin("SHLVL=",ft_itoa(g_glob->shlvl_val));
    ft_export(str);
}

int main(int ac, char **av, char **env)
{
    char *input_str;
    char **new_env;
    t_env *list;
    t_env *tmp;
    t_env *head;
    
    (void)av;
    if(ac != 1)
        return (printf("program doesnt accepts args !"), 0);
    input_str = NULL;
    g_glob = list_env(env);
    g_glob->index = 0;
    g_glob->index_env = 0;
    incrument_shlvl();
    signal_handl();
    rl_catch_signals = 0;
    while(1)
    {
        g_glob->status = 0;
        g_glob->sig = 0;
        list = g_glob;
        tmp = g_glob;
        head = g_glob;
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