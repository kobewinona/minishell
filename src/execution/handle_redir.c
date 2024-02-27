/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:20:11 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/27 11:28:22 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	define_org_fd(t_msh **msh, t_redir *cmd, int *org_fd)
{
	(*org_fd) = UNSPECIFIED;
	if (cmd->type == T_REDIR_STDOUT || cmd->type == T_APPEND_STDOUT)
	{
		if (cmd->fd[1] > 1)
			(*org_fd) = handle_err(dup(cmd->fd[1]),
					msh, T_SYS_ERR, DUP, NULL);
		else
			(*org_fd) = handle_err(dup(STDOUT_FILENO),
					msh, T_SYS_ERR, DUP, NULL);
	}
	else if (cmd->fd[1] == STDERR_FILENO)
		(*org_fd) = handle_err(dup(STDERR_FILENO), msh, T_SYS_ERR, DUP, NULL);
	else
		(*org_fd) = handle_err(dup(STDIN_FILENO), msh, T_SYS_ERR, DUP, NULL);
	if ((*org_fd) < 0)
		return (ERROR);
	return (SUCCESS);
}

static int	restore_org_fd(t_msh **msh, t_redir *cmd, const int *org_fd)
{
	int	res;

	if ((*org_fd) != UNSPECIFIED) {
		if (cmd->fd[1] > 1)
			res = handle_err(dup2((*org_fd), cmd->fd[1]),
					msh, T_SYS_ERR, DUP2, NULL);
		else if (cmd->type == T_REDIR_STDOUT || cmd->type == T_APPEND_STDOUT)
			res = handle_err(dup2((*org_fd), STDOUT_FILENO),
					msh, T_SYS_ERR, DUP2, NULL);
		else if (cmd->fd[1] == STDERR_FILENO)
			res = handle_err(dup2((*org_fd), STDERR_FILENO),
					msh, T_SYS_ERR, DUP2, NULL);
		else
			res = handle_err(dup2((*org_fd), STDIN_FILENO),
					msh, T_SYS_ERR, DUP2, NULL);
	}
	close((*org_fd));
	return (res);
}

int	handle_redir(t_msh **msh, t_redir *cmd)
{
	int	org_fd;
	int	res;

	if (define_org_fd(msh, cmd, &org_fd) == ERROR)
		return (ERROR);
	if (cmd->fd[1] > 1)
		res = handle_err(dup2(cmd->fd[0], cmd->fd[1]),
				msh, T_SYS_ERR, DUP2, NULL);
	else if (cmd->type == T_REDIR_STDOUT || cmd->type == T_APPEND_STDOUT)
		res = handle_err(dup2(cmd->fd[0], STDOUT_FILENO),
				msh, T_SYS_ERR, DUP2, NULL);
	else
		res = handle_err(dup2(cmd->fd[0], STDIN_FILENO),
				msh, T_SYS_ERR, DUP2, NULL);
	if (res != ERROR)
		run_cmd(msh, cmd->subcmd);
	close(cmd->fd[0]);
	return (restore_org_fd(msh, cmd, &org_fd));
}
