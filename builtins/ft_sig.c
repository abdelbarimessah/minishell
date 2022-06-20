/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amessah <amessah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:32:13 by amessah           #+#    #+#             */
/*   Updated: 2022/06/18 06:33:47 by amessah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	sig_handler(int sig)
// {
// 	if (sig == SIGINT && !g_glob->status)
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		g_glob->exit_status = 1;
// 	}
// 	// else if(!kill(g_glob->g_pid, sig))
// 	else if(sig == SIGINT || sig == SIGQUIT)
// 	{
// 		if(sig == SIGQUIT && !g_glob->g_pid )
// 		{
// 			ft_putstr_fd("Quit: 3\n", 1);
// 			g_glob->exit_status = 131;
// 		}
// 		else
// 		{
// 			write(1, "\n", 1);
// 			g_glob->exit_status = 130;
// 		}
// 	}
// }

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

static void	process(int sign_num)
{
	if (!kill(g_glob->g_pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_glob->exit_status = 131;
		}
		else if (sign_num == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g_glob->exit_status = 130;
		}
	}
	else if (sign_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		g_glob->exit_status = 1;
	}
}

void sig_handler(int sig)
{
	if ((sig == SIGINT || sig == SIGQUIT) && g_glob->g_pid != 0)
		process(sig);
	else if(sig == SIGINT && !g_glob->status)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		g_glob->exit_status = 1;
	}
}

void	signal_handl(void)
{
	signal(SIGINT, sig_handler);
	// signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, sig_handler);
	return ;
}