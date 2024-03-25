/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:20:11 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/25 19:12:38 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	define_org_fd(t_msh **msh, t_redir *cmd, int *org_fd)
{
	(*org_fd) = UNSPECIFIED;
	if (cmd->type == R_STDOUT || cmd->type == R_APPEND)
	{
		if (cmd->fd[1] > 1)
			(*org_fd) = dup(cmd->fd[1]);
		else
			(*org_fd) = dup(STDOUT_FILENO);
	}
	else if (cmd->fd[1] == STDERR_FILENO)
		(*org_fd) = dup(STDERR_FILENO);
	else
		(*org_fd) = dup(STDIN_FILENO);
	if ((*org_fd) < 0)
		return (handle_err(msh, SYSTEM, DUP, 1), ERROR);
	return (SUCCESS);
}

static void	restore_org_fd(t_msh **msh, t_redir *cmd, const int *org_fd)
{
	int	res;

	res = SUCCESS;
	if ((*org_fd) != UNSPECIFIED)
	{
		if (cmd->fd[1] > 1)
			res = dup2((*org_fd), cmd->fd[1]);
		else if (cmd->type == R_STDOUT || cmd->type == R_APPEND)
			res = dup2((*org_fd), STDOUT_FILENO);
		else if (cmd->fd[1] == STDERR_FILENO)
			res = dup2((*org_fd), STDERR_FILENO);
		else
			res = dup2((*org_fd), STDIN_FILENO);
	}
	if (res == ERROR)
		handle_err(msh, SYSTEM, DUP2, 1);
	close((*org_fd));
}

void	handle_redir(t_msh **msh, t_redir *cmd)
{
	int	org_fd;
	int	res;

	if (cmd->fd[0] < 0 || (cmd->fd[1] < 0 && cmd->fd[1] != UNSPECIFIED))
		return ;
	if (define_org_fd(msh, cmd, &org_fd) == ERROR)
		return ;
	if (cmd->fd[1] > 1)
		res = dup2(cmd->fd[0], cmd->fd[1]);
	else if (cmd->type == R_STDOUT || cmd->type == R_APPEND)
		res = dup2(cmd->fd[0], STDOUT_FILENO);
	else
		res = dup2(cmd->fd[0], STDIN_FILENO);
	if (res != ERROR)
		run_cmd(msh, cmd->subcmd);
	else
		handle_err(msh, SYSTEM, DUP2, 1);
	close(cmd->fd[0]);
	restore_org_fd(msh, cmd, &org_fd);
}
