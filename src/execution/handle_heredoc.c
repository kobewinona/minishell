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

	input = readline(INPUT_PROMPT);
	while (input)
	{
		if (!ft_strncmp(input, heredoc, ft_strlen(heredoc)))
		{
			free(input);
			break ;
		}
		handle_err((int)write(fd, input, ft_strlen(input)),
			(t_err){T_SYS_ERR, WRITE, input}, true);
		handle_err((int)write(fd, "\n", 1),
			(t_err){T_SYS_ERR, WRITE, "\n"}, true);
		free(input);
		input = readline(INPUT_PROMPT);
	}
}

void	handle_heredoc(t_heredoc *cmd, int output_fd, t_var_node *env_vars)
{
	int		org_stdout;
	int		fd[2];

	org_stdout = 0;
	if (output_fd != UNSPECIFIED)
		org_stdout = handle_err(dup(output_fd), (t_err){T_SYS_ERR, DUP}, true);
	handle_err(pipe(fd), (t_err){T_SYS_ERR, PIPE}, true);
	run_heredoc_mode(cmd->eof, fd[1]);
	close(fd[1]);
	handle_err(dup2(fd[0], STDIN_FILENO), (t_err){T_SYS_ERR, DUP2}, true);
	close(fd[0]);
	if (output_fd != -1)
		handle_err(dup2(output_fd, STDOUT_FILENO),
			(t_err){T_SYS_ERR, DUP2}, true);
	run_cmd(cmd->subcmd, env_vars);
	dup2(org_stdout, STDOUT_FILENO);
	close(org_stdout);
}
