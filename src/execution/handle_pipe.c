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

	handle_err(pipe(fd), PIPE, NULL, true);
	if (handle_err(fork(), FORK, NULL, true) == 0)
	{
        close(STDOUT_FILENO);
		handle_err(dup2(fd[1], STDOUT_FILENO), DUP2, NULL, true);
		close(fd[0]);
        close(fd[1]);
		run_cmd(params->from);
        exit(EXIT_SUCCESS);
	}
    if (handle_err(fork(), FORK, NULL, true) == 0)
    {
        close(STDIN_FILENO);
        handle_err(dup2(fd[0], STDIN_FILENO), DUP2, NULL, true);
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
