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

void	handle_pipe(t_pipe *params)
{
	int	fd[2];

	handle_err(pipe(fd), (t_err){T_SYS_ERR, PIPE}, true);
	if (handle_err(fork(), (t_err){T_SYS_ERR, FORK}, true) == 0)
	{
		close(STDOUT_FILENO);
		handle_err(dup2(fd[1], STDOUT_FILENO), (t_err){T_SYS_ERR, DUP2}, true);
		close(fd[0]);
		close(fd[1]);
		run_cmd(params->from);
		exit(EXIT_SUCCESS);
	}
	if (handle_err(fork(), (t_err){T_SYS_ERR, DUP2}, true) == 0)
	{
		close(STDIN_FILENO);
		handle_err(dup2(fd[0], STDIN_FILENO), (t_err){T_SYS_ERR, DUP2}, true);
		close(fd[0]);
		close(fd[1]);
		run_cmd(params->to);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}
