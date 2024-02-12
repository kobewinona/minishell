/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:55:34 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/19 01:55:35 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_heredoc_mode(const char *heredoc, int fd)
{
	char	*input;

	input = readline(PROMPT);
	while (input)
	{
		if (!ft_strncmp(input, heredoc, ft_strlen(heredoc)))
		{
			free(input);
			break ;
		}
		handle_err((int)write(fd, input, ft_strlen(input)), WRITE, input, true);
		handle_err((int)write(fd, "\n", 1), WRITE, "\n", true);
		free(input);
		input = readline(PROMPT);
	}
}

void	handle_heredoc(t_heredoc *params, int output_fd)
{
	int		org_stdout;
	int		fd[2];

	org_stdout = 0;
	if (output_fd != -1)
		org_stdout = handle_err(dup(output_fd), DUP, NULL, true);
	handle_err(pipe(fd), PIPE, NULL, true);
	run_heredoc_mode(params->eof, fd[1]);
	close(fd[1]);
	handle_err(dup2(fd[0], STDIN_FILENO), DUP2, NULL, true);
	close(fd[0]);
	if (output_fd != -1)
		handle_err(dup2(output_fd, STDOUT_FILENO), DUP2, NULL, true);
	run_cmd(params->subcmd);
	dup2(org_stdout, STDOUT_FILENO);
	close(org_stdout);
}