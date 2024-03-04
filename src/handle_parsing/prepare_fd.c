/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:03:42 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/04 15:03:43 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prepare_fd(t_msh **msh, t_redir *cmd)
{
	int	pipe_fds[2];
	int	prepared_fd;

	if (cmd->type == T_HEREDOC)
	{
		if (pipe(pipe_fds) == ERROR)
			return (print_err(msh, (t_err){T_SYS_ERR, PIPE}, false).t_int);
		write(pipe_fds[1], cmd->f, strlen(cmd->f));
		close(pipe_fds[1]);
		return (pipe_fds[0]);
	}
	prepared_fd = open(cmd->f, cmd->mode, RW_R_R_PERM);
	if (prepared_fd < 0)
		return (print_err(msh, (t_err){T_SYS_ERR, cmd->f}, false).t_int);
	return (prepared_fd);
}

void	prepare_fds(t_msh **msh, t_cmd **cmd)
{
	if (!(*cmd))
		return ;
	if ((*cmd)->type == T_PIPE)
	{
		prepare_fds(msh, &(*cmd)->pipe.from);
		prepare_fds(msh, &(*cmd)->pipe.to);
	}
	if ((*cmd)->type == T_REDIR)
	{
		(*cmd)->redir.fd[0] = prepare_fd(msh, &(*cmd)->redir);
		if ((*cmd)->redir.fd[0] == ERROR)
		{
			cleanup_cmds(&(*cmd));
			return ;
		}
		if ((*cmd)->redir.subcmd->type == T_REDIR)
			prepare_fds(msh, &(*cmd)->redir.subcmd);
	}
}
