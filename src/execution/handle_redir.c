/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:20:11 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/20 18:50:34 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir(t_msh **msh, t_redir *cmd)
{
	int	org_fd;

	if (cmd->type == T_REDIR_STDOUT || cmd->type == T_APPEND_STDOUT)
	{
		org_fd = dup(STDOUT_FILENO);
		dup2(cmd->fd, STDOUT_FILENO);
	}
	else
	{
		org_fd = dup(STDIN_FILENO);
		dup2(cmd->fd, STDIN_FILENO);
	}
	run_cmd(msh, cmd->subcmd);
	if (cmd->type == T_REDIR_STDOUT || cmd->type == T_APPEND_STDOUT)
		dup2(org_fd, STDOUT_FILENO);
	else
		dup2(org_fd, STDIN_FILENO);
	close(org_fd);
	close(cmd->fd);
}
