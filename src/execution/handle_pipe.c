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
		handle_err(ERROR, NULL, MALLOC, true);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!cmd->pipe)
	{
		free(cmd);
		handle_err(ERROR, NULL, MALLOC, true);
	}
	ft_memset(cmd->pipe, 0, sizeof(t_cmd));
	cmd->type = PIPE_CMD;
	cmd->pipe->from = cmd1;
	cmd->pipe->to = cmd2;
	return (cmd);
}

void	handle_pipe(t_pipe *params)
{
	int	fd[2];

	handle_err(pipe(fd), PIPE, NULL, true);
	if (handle_err(fork(), FORK, NULL, true) == 0)
	{
		handle_err(dup2(fd[1], STDOUT_FILENO), DUP2, NULL, true);
		close(fd[0]);
		run_cmd(params->from);
	}
	handle_err(dup2(fd[0], STDIN_FILENO), DUP2, NULL, true);
	close(fd[1]);
	run_cmd(params->to);
}
