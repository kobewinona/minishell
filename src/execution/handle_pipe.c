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
	int	exit_status;

	exit_status = 0;
	pid = handle_err(fork(), msh, T_SYS_ERR, FORK, NULL);
	if (pid == ERROR)
		process_err(msh, false);
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
		run_cmd(msh, cmd);
		exit(EXIT_SUCCESS);
	}
	wait(&exit_status);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (SUCCESS);
}

int	handle_pipe(t_msh **msh, t_pipe *cmd)
{
	int	pipe_fds[2];
	int	ext_code_left;
	int	ext_code_right;

	if (handle_err(pipe(pipe_fds), msh, T_SYS_ERR, PIPE, NULL) != SUCCESS)
		return (ERROR);
	ext_code_left = run_pipe_end(msh, cmd->from, pipe_fds, STDOUT_FILENO);
	ext_code_right = run_pipe_end(msh, cmd->to, pipe_fds, STDIN_FILENO);
	close(pipe_fds[STDIN_FILENO]);
	close(pipe_fds[STDOUT_FILENO]);
	
	(*msh)->exit_code = ext_code_right;
	if ((*msh)->pid != getpid())
		exit(ext_code_right);

	printf("Pipe result: %d\n", ext_code_right);
	return (ext_code_right);
}
