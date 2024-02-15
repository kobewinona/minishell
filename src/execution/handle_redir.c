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

void	handle_redir(t_redir *cmd)
{
	int		org_stdout;
	int		new_fd;
	int		redir_fd;

	redir_fd = STDOUT_FILENO;
	new_fd = handle_err(open(cmd->file, cmd->mode, RW_R_R_PERM),
			(t_err){T_SYS_ERR, NULL, cmd->file}, true);
	if (cmd->type == T_REDIR_STDIN)
		redir_fd = STDIN_FILENO;
	if (cmd->subcmd->type == T_HEREDOC)
		return (handle_heredoc(&(cmd->subcmd->heredoc), new_fd));
	org_stdout = handle_err(dup(redir_fd),
			(t_err){T_SYS_ERR, DUP, NULL}, true);
	handle_err(dup2(new_fd, redir_fd),
		(t_err){T_SYS_ERR, DUP2, NULL}, true);
	run_cmd(cmd->subcmd);
	close(new_fd);
	handle_err(dup2(org_stdout, redir_fd),
		(t_err){T_SYS_ERR, DUP2, NULL}, true);
	close(org_stdout);
	exit(EXIT_SUCCESS);
}
