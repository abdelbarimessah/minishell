/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:23:07 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/06/21 15:51:28 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_create_tokens(struct s_list **node, char *str, char **env)
{
	int		i;
	int		j;
	char	*sb;
	char	*s;
	char	*st;
	t_env	*tmp;
	char	*limiter;
	char	**env1;

	(void)env;
	i = 0;
	j = 1;
	tmp = g_glob;
	env1 = new_env_function(tmp);
	while (str[i] == ' ')
		i++;
	while (i < ft_strlen(str))
	{
		j = 0;
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			if (!str[i])
				break ;
			ft_lstadd_back(node, ft_lstnew(ft_strdup(" "), WSPACE));
			i--;
		}
		else if (str[i] == '|')
			ft_lstadd_back(node, ft_lstnew(ft_strdup("|"), PIP));
		else if (str[i] == '"')
		{
			j = ft_checker1(node, str, i, env1);
			if (j == -1)
				return (0);
			i += j + 1;
		}
		else if (str[i] == '\'')
		{
			j = ft_checker2(node, str, i);
			if (j == -1)
			{
				printf("single quotes not closed !\n");
				return (0);
			}
			i += j + 1;
		}
		else if (str[i] == '$')
		{
			if (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '$')
			{
				ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WORD));
				i++;
			}
			else if (str[i + 1] == '?')
			{
				ft_lstadd_back(node, ft_lstnew
					(ft_strdup(ft_itoa(g_glob->exit_status)), WORD));
				i++;
			}
			else if (ft_isdigitt(str[i + 1]))
			{
				i++;
				s = ft_substr(str, i, j - i);
				if (s)
					ft_lstadd_back(node, ft_lstnew(ft_strdup(s), WORD));
			}
			else
			{
				j = i + 1;
				while (ft_isdigitt(str[j])
					|| ft_isalphaa(str[j]) || str[j] == '_')
					j++;
				st = ft_substr(str, i, j - i);
				s = get_from_env(env1, ft_substr(str, i + 1, j - (i + 1)));
				if (s)
					ft_lstadd_back(node, ft_lstnew(ft_strdup(s), WORD));
				else if (str[i + 1] == '/')
					ft_lstadd_back(node, ft_lstnew(ft_strdup(st), WORD));
				i += (j - i);
			}
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			i++;
			ft_lstadd_back(node, ft_lstnew(ft_strdup(">>"), OUTPUTE_HEREDOC));
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			limiter = ft_strdup("");
			i += 2;
			ft_lstadd_back(node, ft_lstnew(ft_strdup("<<"), INTPUTE_HEREDOC));
			while (str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' '
				&& str[i] != '<'
				&& str[i] != '>' && str[i] != '|')
			{
				if (str[i] == '"')
				{
					if (str[i] == '"' && str[i + 1] == '"')
					{
						sb = ft_strdup("");
						i += 2;
						j = 1;
					}
					else
					{
						i++;
						j = 0;
						while (str[i] && str[i] != '"')
						{
							i++;
							j++;
						}
						if (!str[i])
							return (printf("double quotes not closed !\n"), 0);
						else
						{
							sb = ft_substr(str, i - j, j);
							limiter = ft_strjoin(limiter, sb);
						}
						i++;
					}
				}
				else if (str[i] == '\'')
				{
					if (str[i] == '\'' && str[i + 1] == '\'')
					{
						sb = ft_strdup("");
						i += 2;
						j = 1;
					}
					else
					{
						i++;
						j = 0;
						while (str[i] && str[i] != '\'')
						{
							i++;
							j++;
						}
						if (!str[i])
							return (printf("single quotes not closed !\n"), 0);
						else
						{
							sb = ft_substr(str, i - j, j);
							limiter = ft_strjoin(limiter, sb);
						}
						i++;
					}
				}
				else
				{
					j = 0;
					while (str[i] && str[i] != '\'' && str[i] != '"'
						&& str[i] != ' ' && str[i] != '<'
						&& str[i] != '>' && str[i] != '|')
					{
						i++;
						j++;
					}
					sb = ft_substr(str, i - j, j);
					limiter = ft_strjoin(limiter, sb);
				}
				free(sb);
			}
			ft_lstadd_back(node, ft_lstnew(ft_strdup(limiter), LIMITERR));
			free(limiter);
			j = 5;
		}
		else if (str[i] == '>' && str[i + 1] != '>')
			ft_lstadd_back(node, ft_lstnew(ft_strdup(">"), OUTPUTE_REDI));
		else if (str[i] == '<' && str[i + 1] != '<')
			ft_lstadd_back(node, ft_lstnew(ft_strdup("<"), INPUTE_REDI));
		else
		{
			if (str[i] != ' ')
			{
				i--;
				while (check_str(str, ++i))
					j++;
				ft_lstadd_back(node, ft_lstnew
					(ft_substr(str, i - j, j), WORD));
			}
		}
		if (!j)
			i++;
	}
	ft_lstadd_back(node, ft_lstnew(ft_strdup("---"), END_TOK));
	return (1);
}

void	ft_join_pipe(t_list *node, char **env)
{
	t_list	*head;
	char	*str;
	char	**str_split;
	int		num_com;

	str = ft_strdup("");
	head = node->next;
	while (head)
	{
		if (head->token == PIP)
			str = ft_strjoin(str, "|");
		else if (head->token == OUTPUTE_HEREDOC)
		{
			head = head->next;
			while (head->token == WSPACE && head->token != END_TOK)
				head = head->next;
		}
		else if (head->token == INTPUTE_HEREDOC)
			head = head->next;
		else if (head->token == OUTPUTE_REDI)
		{
			head = head->next;
			while (head->token == WSPACE && head->token != END_TOK)
				head = head->next;
		}
		else if (head->token == INPUTE_REDI)
		{
			head = head->next;
			while (head->token == WSPACE && head->token != END_TOK)
				head = head->next;
		}
		else if (head->token == WSPACE)
			str = ft_strjoin(str, "\v");
		else if (head->token == NUL)
			str = ft_strjoin(str, ft_strdup(" "));
		else if (head->token == WORD)
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	str_split = ft_split(str, '|');
	num_com = num_commande(str_split);
	free(str);
	main_pipe(num_com, str_split, env, node);
	exit(1);
}

void	execute_tb(char *cmds, char **env, t_list *node, t_vars var)
{
	char	*path;
	char	**cmd;
	int		end_p[2];
	int		a;
	int		k;

	a = 0;
	k = -1;
	while (cmds[++k])
	{
		if (cmds[k] == ' ' && cmds[k] != '\v')
			a = 1;
	}
	if (a)
		cmd = ft_split(cmds, ' ');
	else
		cmd = ft_split(cmds, '\v');
	if (check_tok(node, INTPUTE_HEREDOC))
	{
		if (!ft_is_last(node, INTPUTE_HEREDOC, INPUTE_REDI, END_TOK))
		{
			dup2(var.fdd[0], var.z[0]);
			close(var.fdd[0]);
		}
		else
		{
			if (pipe(end_p) == -1)
				perror("error");
			ft_putstr_fd(var.value, end_p[1]);
			close(end_p[1]);
			dup2(end_p[0], 0);
			close(end_p[0]);
		}
	}
	if (var.z[0] == 0)
	{
		dup2(var.fdd[0], var.z[0]);
		close(var.fdd[0]);
	}
	if (var.z[1] == 1)
	{
		dup2(var.fdd[1], var.z[1]);
		close(var.fdd[1]);
	}
	path = ft_path(env, cmds);
	if (access(cmd[0], X_OK) == 0)
		path = cmd[0];
	if (execve(path, cmd, env) == -1)
	{
		perror("Error");
		exit (1);
	}	
}

void	ft_execute_comnd(t_list *node, char **env)
{
	t_list	*head;
	t_vars	var;
	char	*str;
	int		pid;
	char	*file_n;
	char	**cmd;
	char	*p;

	var.fdd[0] = dup(0);
	var.fdd[1] = dup(1);
	head = node;
	str = ft_strdup("");
	head = head->next;
	while (head)
	{
		if (head->token == WSPACE)
			str = ft_strjoin(str, "\v");
		else if (head->token == INPUTE_REDI)
		{	
			file_n = ft_strdup("");
			head = head->next;
			if (head->token == WSPACE)
				head = head->next;
			while (head->token == WORD && head->token != END_TOK)
			{
				file_n = ft_strjoin(file_n, head->content);
				head = head->next;
			}
			var.fdd[0] = open(file_n, O_RDONLY);
			if (var.fdd[0] == -1)
			{
				printf(" ---> %s <----- No such file or directory\n", file_n);
				return ;
			}
			free(file_n);
			var.z[0] = 0;
		}
		else if (head->token == INTPUTE_HEREDOC)
		{
			var.value = ft_strdup("");
			head = head->next;
			while (head->token == WSPACE && head->token != END_TOK)
				head = head->next;
			while (1)
			{
				p = readline("> ");
				if (!ft_strcmp_2(p, head->content))
					break ;
				p = ft_strjoin_nf(p, "\n");
				var.value = ft_strjoin(var.value, p);
				free(p);
			}
		}
		else if (head->token == OUTPUTE_HEREDOC)
		{
			file_n = ft_strdup("");
			head = head->next;
			if (head->token == WSPACE)
				head = head->next;
			while (head->token == WORD && head->token != END_TOK)
			{
				file_n = ft_strjoin(file_n, head->content);
				head = head->next;
			}
			var.fdd[1] = open(file_n, O_CREAT | O_WRONLY | O_APPEND, 0777);
			if (var.fdd[1] == -1)
			{
				printf(" %s Error in file creation\n", file_n);
				return ;
			}
			free(file_n);
			var.z[1] = 1;
		}
		else if (head->token == OUTPUTE_REDI)
		{
			file_n = ft_strdup("");
			head = head->next;
			if (head->token == WSPACE)
				head = head->next;
			while (head->token == WORD && head->token != END_TOK)
			{
				file_n = ft_strjoin(file_n, head->content);
				head = head->next;
			}
			var.fdd[1] = open(file_n, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (var.fdd[1] == -1)
			{
				printf(" %s Error in file creation\n", file_n);
				return ;
			}
			free(file_n);
			var.z[1] = 1;
		}
		else if (head->token == NUL)
			str = ft_strjoin(str, " ");
		else if (head->token == WORD)
			str = ft_strjoin(str, head->content);
		head = head->next;
	}
	cmd = ft_split(str, '\v');
	if (!cmd[0] || !str[0])
		return ;
	else
	{
		pid = fork();
		g_glob->g_pid = pid;
		if (pid == 0)
			execute_tb(str, env, node, var);
		else
			g_glob->status = 1;
		waitpid(pid, NULL, 0);
		status_child();
	}
	free(str);
	ft_free(cmd);
}

void	tokenizer(char *str, char **env)
{
	int		i;
	int		j;
	pid_t	pid;
	t_list	*token;
	t_list	*head;

	i = 0;
	j = 1;
	if (str[0] == '\0')
		return ;
	token = ft_lstnew(ft_strdup("---"), START_TOK);
	head = token;
	if (!ft_create_tokens(&token, str, env))
		return ;
	if (!check_syntax_list(head))
	{
		ft_error("syntax error ! \n", 0);
		return ;
	}
	if (check_tok(head, PIP))
	{
		pid = fork();
		if (pid == 0)
			ft_join_pipe(head, env);
		waitpid(pid, NULL, 0);
	}
	else if (ft_execute_builtins(head, env) == 1)
		test_builtins(head, env);
	else if (ft_execute_builtins(head, env) == 0)
		ft_execute_comnd(head, env);
	ft_lstclear(&head);
}
