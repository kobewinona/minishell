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
//	printf("cmd type %s %s\n", cmd->type == EXEC ? "EXEC" : "PIPE", cmd->type == EXEC ? cmd->exec->argv[0]: "");
	if (cmd->type == EXEC)
		handle_exec(cmd->exec);
	if (cmd->type == PIPE)
		handle_pipe(cmd->pipe);
}

static t_cmd	*construct_exec_cmd(char **argv)
{
	t_cmd	*cmd;

	if (argv[0] == NULL)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		handle_exit(EXIT_FAILURE);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->exec = (t_exec *)malloc(sizeof(t_exec));
	if (!cmd->exec)
	{
		free(cmd);
		handle_exit(EXIT_FAILURE);
	}
	ft_memset(cmd->exec, 0, sizeof(t_cmd));
	cmd->type = EXEC;
	cmd->exec->argv = argv;
	return (cmd);
}

static t_cmd	*construct_pipe_cmd(t_cmd *cmd1, t_cmd *cmd2)
{
	t_cmd	*cmd;

	if (!cmd1 || !cmd2)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		handle_exit(EXIT_FAILURE);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!cmd->pipe)
	{
		free(cmd);
		handle_exit(EXIT_FAILURE);
	}
	ft_memset(cmd->pipe, 0, sizeof(t_cmd));
	cmd->type = PIPE;
	cmd->pipe->from = cmd1;
	cmd->pipe->to = cmd2;
	return (cmd);
}

static t_cmd	*parse_cmd(char *input)
{
	t_cmd	*exec_cmd1;
	t_cmd	*exec_cmd2;
	t_cmd	*exec_cmd3;
	t_cmd	*pipe_cmd1;
	t_cmd	*pipe_cmd2;

	exec_cmd1 = NULL;
	exec_cmd2 = NULL;
	exec_cmd2 = NULL;
	pipe_cmd1 = NULL;
	pipe_cmd2 = NULL;
	exec_cmd1 = construct_exec_cmd(ft_split(ft_strtok(input, "|"), ' '));
	exec_cmd2 = construct_exec_cmd(ft_split(ft_strtok(NULL, "|"), ' '));
	exec_cmd3 = construct_exec_cmd(ft_split(ft_strtok(NULL, "|"), ' '));
	if (exec_cmd1 && exec_cmd2)
		pipe_cmd1 = construct_pipe_cmd(exec_cmd1, exec_cmd2);
	if (pipe_cmd1 && exec_cmd3)
		pipe_cmd2 = construct_pipe_cmd(pipe_cmd1, exec_cmd3);
	if (pipe_cmd2)
		return (pipe_cmd2);
	if (pipe_cmd1)
		return (pipe_cmd1);
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
		if (input[0] == 'c' && input[1] == 'd')
			cd(ft_split(input, ' '));
		if (fork() == 0)
			run_cmd(parse_cmd(input));
		free(input);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}
