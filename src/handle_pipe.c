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

// TODO check if dup2 return on error
void	handle_pipe(t_pipe *pipe_params)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		handle_exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		handle_exit(EXIT_FAILURE);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		run_cmd(pipe_params->from);
	}
	waitpid(pid, NULL, 0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	run_cmd(pipe_params->to);
}
