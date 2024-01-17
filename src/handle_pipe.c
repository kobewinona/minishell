/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:11:03 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/16 16:11:04 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*construct_pipe_cmd(t_cmd *cmd1, t_cmd *cmd2)
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

void	handle_pipe(t_pipe *pipe_params)
{
	int	fd[2];

	if (pipe(fd) == ERROR)
		handle_exit(EXIT_FAILURE);
	if (fork1() == 0)
	{
		dup3(fd[1], STDOUT_FILENO);
		close(fd[0]);
		run_cmd(pipe_params->from);
	}
	wait(NULL);
	dup3(fd[0], STDIN_FILENO);
	close(fd[1]);
	run_cmd(pipe_params->to);
}
