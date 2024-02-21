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

void	handle_pipe(t_pipe *cmd)
{
	int	pipe_fds[2];

	handle_err(pipe(pipe_fds), (t_err){T_SYS_ERR, PIPE}, true);
	if (handle_err(fork(), (t_err){T_SYS_ERR, FORK}, true) == 0)
	{
		close(STDOUT_FILENO);
		handle_err(dup2(pipe_fds[1], STDOUT_FILENO),
			(t_err){T_SYS_ERR, DUP2}, true);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		run_cmd(cmd->from);
		exit(EXIT_SUCCESS);
	}
	if (handle_err(fork(), (t_err){T_SYS_ERR, DUP2}, true) == 0)
	{
		close(STDIN_FILENO);
		handle_err(dup2(pipe_fds[0], STDIN_FILENO),
			(t_err){T_SYS_ERR, DUP2}, true);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		run_cmd(cmd->to);
		exit(EXIT_SUCCESS);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	wait(NULL);
	wait(NULL);
}
