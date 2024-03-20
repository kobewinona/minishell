/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:03:42 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/20 22:26:53 by dklimkin         ###   ########.fr       */
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
			return (handle_err(msh, (t_err){T_SYS_ERR, PIPE}, false), ERROR);
		write(pipe_fds[1], cmd->f, strlen(cmd->f));
		close(pipe_fds[1]);
		free(cmd->f);
		return (pipe_fds[0]);
	}
	prepared_fd = open(cmd->f, cmd->mode, RW_R_R_PERM);
	if (prepared_fd < 0)
		return (handle_err(msh, (t_err){T_SYS_ERR,
				cmd->f, NULL}, false), ERROR);
	return (prepared_fd);
}

int	prepare_fds(t_msh **msh, t_cmd **cmd)
{
	if (!(*cmd))
		return (ERROR);
	if ((*cmd)->type == T_PIPE)
	{
		if (prepare_fds(msh, &(*cmd)->pipe.from) == ERROR)
			return (ERROR);
		if (prepare_fds(msh, &(*cmd)->pipe.to) == ERROR)
			return (ERROR);
	}
	if ((*cmd)->type == T_REDIR)
	{
		(*cmd)->redir.fd[0] = prepare_fd(msh, &(*cmd)->redir);
		if ((*cmd)->redir.fd[0] == ERROR)
			return (ERROR);
		if ((*cmd)->redir.subcmd->type == T_REDIR)
		{
			if (prepare_fds(msh, &(*cmd)->redir.subcmd))
				return (ERROR);
		}
	}
	return (SUCCESS);
}
