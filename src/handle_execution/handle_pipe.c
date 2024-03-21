/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:11:03 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 08:05:12 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_pipe_end(t_msh **msh, t_cmd *cmd, int *pipe_fds, int end)
{
	if (cmd->type != T_PIPE)
	{
		(*msh)->curr_pid = fork();
		if ((*msh)->curr_pid == ERROR)
			return (handle_err(msh, SYSTEM, FORK, 1), ERROR);
		if ((*msh)->curr_pid == 0)
		{
			if (setup_signal(SIGINT, SIG_DFL) == ERROR)
				handle_exit(msh, EXIT_FAILURE);
			if (dup2(pipe_fds[end], end) == ERROR)
				return (handle_err(msh, SYSTEM, DUP2, 1), ERROR);
			close(pipe_fds[STDIN_FILENO]);
			close(pipe_fds[STDOUT_FILENO]);
			run_cmd(msh, cmd);
			handle_exit(msh, (*msh)->exit_code);
		}
		return ((*msh)->curr_pid);
	}
	if (dup2(pipe_fds[STDIN_FILENO], STDIN_FILENO) == ERROR)
		return (handle_err(msh, SYSTEM, DUP2, 1), ERROR);
	close(pipe_fds[STDIN_FILENO]);
	close(pipe_fds[STDOUT_FILENO]);
	run_cmd(msh, cmd);
	return ((*msh)->curr_pid);
}

void	handle_pipe(t_msh **msh, t_pipe *cmd)
{
	int	pipe_fds[2];
	int	exit_code;
	int	cmd_from_pid;
	int	cmd_to_pid;

	g_state = IS_EXEC;
	exit_code = EXIT_SUCCESS;
	if (pipe(pipe_fds) == ERROR)
		return (handle_err(msh, SYSTEM, PIPE, 1));
	cmd_from_pid = run_pipe_end(msh, cmd->from, pipe_fds, STDOUT_FILENO);
	if (cmd_from_pid == ERROR)
		return ;
	cmd_to_pid = run_pipe_end(msh, cmd->to, pipe_fds, STDIN_FILENO);
	if (cmd_to_pid == ERROR)
		return ;
	close(pipe_fds[STDIN_FILENO]);
	close(pipe_fds[STDOUT_FILENO]);
	waitpid(cmd_from_pid, NULL, 0);
	if (cmd->to->type != T_PIPE)
	{
		waitpid(cmd_to_pid, &exit_code, 0);
		update_exit_code(msh, exit_code);
		dup2((*msh)->org_fd, STDIN_FILENO);
	}
	g_state = IS_IDLE;
}
