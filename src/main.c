/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:24:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/10 14:24:21 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd(t_cmd *cmd)
{
	if (cmd->type == EXEC)
	{
		if (ft_strncmp(cmd->exec->argv[0], CD, ft_strlen(CD)) != 0)
			handle_exec(cmd->exec);
	}
	if (cmd->type == PIPE)
		handle_pipe(cmd->pipe);
	if (cmd->type == REDIR)
		handle_redir(cmd->redir);
}

static t_cmd	*parse_cmd(char *input)
{
	t_cmd	*exec_cmd1 = NULL;
	t_cmd	*exec_cmd2 = NULL;
	t_cmd	*exec_cmd3 = NULL;
	t_cmd	*pipe_cmd1 = NULL;
	t_cmd	*pipe_cmd2 = NULL;

	exec_cmd1 = construct_exec_cmd(ft_split(ft_strtok(input, "|"), ' '));
//	exec_cmd2 = construct_exec_cmd(ft_split(ft_strtok(NULL, "|"), ' '));
//	exec_cmd3 = construct_exec_cmd(ft_split(ft_strtok(NULL, "|"), ' '));
//	if (exec_cmd1 && exec_cmd2)
//		pipe_cmd1 = construct_pipe_cmd(exec_cmd1, exec_cmd2);
//	if (pipe_cmd1 && exec_cmd3)
//		pipe_cmd2 = construct_pipe_cmd(pipe_cmd1, exec_cmd3);
//	if (pipe_cmd2)
//		return (pipe_cmd2);
//	if (pipe_cmd1)
//		return (pipe_cmd1);
	return (exec_cmd1);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		handle_cd(input);
		if (fork() == 0)
			run_cmd(parse_cmd(input));
		free(input);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}
