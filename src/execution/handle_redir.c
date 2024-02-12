/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:20:11 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/16 22:20:13 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir(t_redir *params)
{
	int		org_stdout;
	int		new_fd;
	int		redir_fd;

	redir_fd = 1;
	new_fd = handle_err(open(params->file, params->mode, RW_R_R_PERM),
			NULL, params->file, true);
	if (params->type == REDIR_STDOUT || params->type == APPEND_STDOUT)
		redir_fd = STDOUT_FILENO;
	if (params->type == REDIR_STDIN)
		redir_fd = STDIN_FILENO;
	if (params->subcmd->type == HEREDOC)
		return (handle_heredoc(params->subcmd->heredoc, new_fd));
	org_stdout = handle_err(dup(redir_fd), DUP, NULL, true);
	handle_err(dup2(new_fd, redir_fd), DUP2, NULL, true);
	run_cmd(params->subcmd);
	close(new_fd);
	handle_err(dup2(org_stdout, redir_fd), DUP2, NULL, true);
	close(org_stdout);
	exit(EXIT_SUCCESS);
}