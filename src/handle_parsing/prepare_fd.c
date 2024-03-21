/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:03:42 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 22:40:21 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prepare_fd(t_msh **msh, t_redir *cmd)
{
	int		pipe_fds[2];
	int		prepared_fd;
	char	*heredoct_input;

	if (cmd->type == T_HEREDOC)
	{
		heredoct_input = collect_heredoc_input(msh, cmd->f);
		if (!heredoct_input)
			return (ERROR);
		if (pipe(pipe_fds) == ERROR)
			return (handle_err(msh, SYSTEM, PIPE, 1), ERROR);
		write(pipe_fds[1], heredoct_input, strlen(heredoct_input));
		close(pipe_fds[1]);
		free(heredoct_input);
		return (pipe_fds[0]);
	}
	prepared_fd = open(cmd->f, cmd->mode, RW_R_R_PERM);
	if (prepared_fd < 0)
		return (handle_err(msh, SYSTEM, cmd->f, 1), ERROR);
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
