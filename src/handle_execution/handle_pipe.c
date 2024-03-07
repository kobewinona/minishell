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

static int	run_pipe_end(t_msh **msh, t_cmd *cmd, int *pipe_fds, int end)
{
	(*msh)->child_pid = fork2(msh);
	if ((*msh)->child_pid == ERROR)
		return (handle_err(msh, (t_err){T_SYS_ERR, FORK}, false).t_int);
	if ((*msh)->child_pid == 0)
	{
		if (dup2(pipe_fds[end], end) == ERROR)
			return (handle_err(msh, (t_err){T_SYS_ERR, DUP2}, true).t_int);
		if (end == STDOUT_FILENO)
			close(pipe_fds[STDIN_FILENO]);
		if (end == STDIN_FILENO)
			close(pipe_fds[STDOUT_FILENO]);
		exit(run_cmd(msh, cmd));
	}
	return ((*msh)->child_pid);
}

int	handle_pipe(t_msh **msh, t_pipe *cmd)
{
	int	pipe_fds[2];
	int	exit_code;
	int	cmd_from_pid;
	int	cmd_to_pid;

	exit_code = 0;
	if (pipe(pipe_fds) == ERROR)
		return (handle_err(msh, (t_err){T_SYS_ERR, PIPE}, false).t_int);
	cmd_from_pid = run_pipe_end(msh, cmd->from, pipe_fds, STDOUT_FILENO);
	if (cmd_from_pid == ERROR)
		return ((*msh)->exit_code);
	cmd_to_pid = run_pipe_end(msh, cmd->to, pipe_fds, STDIN_FILENO);
	if (cmd_to_pid == ERROR)
		return ((*msh)->exit_code);
	close(pipe_fds[STDIN_FILENO]);
	close(pipe_fds[STDOUT_FILENO]);
	waitpid(cmd_from_pid, NULL, 0);
	waitpid(cmd_to_pid, &exit_code, 0);
	collect_exit_code(msh, exit_code);
	return (exit_code);
}
