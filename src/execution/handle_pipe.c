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
	int	pid;

	pid = handle_err(fork(), msh, T_SYS_ERR, FORK, NULL);
	if (pid == ERROR)
		return (ERROR);
	if (pid == 0)
	{
		if (handle_err(dup2(pipe_fds[end], end),
				msh, T_SYS_ERR, DUP2, NULL) == ERROR)
			process_err(msh, true);
		if (end == STDOUT_FILENO)
			close(pipe_fds[STDIN_FILENO]);
		if (handle_err(dup2(pipe_fds[end], end),
				msh, T_SYS_ERR, DUP2, NULL) == ERROR)
			process_err(msh, true);
		if (end == STDIN_FILENO)
			close(pipe_fds[STDOUT_FILENO]);
		close(pipe_fds[STDIN_FILENO]);
		close(pipe_fds[STDOUT_FILENO]);
		// if (run_cmd(msh, cmd) == ERROR)
		// 	process_err(msh, true);
		run_cmd(msh, cmd);
		printf("GOTHERE\n");
		exit((*msh)->exit_code);
	}
	return (SUCCESS);
}

int	handle_pipe(t_msh **msh, t_pipe *cmd)
{
	int	pipe_fds[2];
	int	ext_status_left;
	int ext_status_right;

	ext_status_left = 0;
	ext_status_right = 0;
	if (handle_err(pipe(pipe_fds), msh, T_SYS_ERR, PIPE, NULL) != SUCCESS)
		return (ERROR);
	if (run_pipe_end(msh, cmd->from, pipe_fds, STDOUT_FILENO) == ERROR)
	{
		process_err(msh, false);
		return (ERROR);
	}
	if (run_pipe_end(msh, cmd->to, pipe_fds, STDIN_FILENO) == ERROR)
	{
		process_err(msh, false);
		return (ERROR);
	}
	close(pipe_fds[STDIN_FILENO]);
	close(pipe_fds[STDOUT_FILENO]);
	// wait(NULL);
	// wait(NULL);
	wait(&ext_status_left);
	wait(&ext_status_right);

	ext_status_left = WEXITSTATUS(ext_status_left);
	printf("Pipe result = %d\n", ext_status_left);
	ext_status_right = WEXITSTATUS(ext_status_right);

	printf("Pipe result = %d\n", ext_status_right);
	return (SUCCESS);
}
