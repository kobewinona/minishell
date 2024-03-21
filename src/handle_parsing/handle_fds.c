/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:03:42 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/22 03:09:53 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arb_fd(char **s)
{
	int	fd;
	int	i;

	fd = UNSPECIFIED;
	i = (int)ft_strlen(*s) - 1;
	if ((*s) && !is_emptystr(*s))
	{
		while ((*s) && !ft_isspace((*s)[i]))
			i--;
		fd = ft_atoi(&(*s)[i]);
		if (fd > 0)
			(*s)[i] = '\0';
	}
	return (fd);
}

static int	prepare_fd(t_msh **msh, t_redir *cmd)
{
	int		pipe_fds[2];
	int		prepared_fd;
	char	*heredoct_input;

	if (cmd->type == R_HEREDOC)
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
	if ((*cmd)->type == C_PIPE)
	{
		if (prepare_fds(msh, &(*cmd)->pipe.from) == ERROR)
			return (ERROR);
		if (prepare_fds(msh, &(*cmd)->pipe.to) == ERROR)
			return (ERROR);
	}
	if ((*cmd)->type == C_REDIR)
	{
		(*cmd)->redir.fd[0] = prepare_fd(msh, &(*cmd)->redir);
		if ((*cmd)->redir.fd[0] == ERROR)
			return (ERROR);
		if ((*cmd)->redir.subcmd->type == C_REDIR)
		{
			if (prepare_fds(msh, &(*cmd)->redir.subcmd))
				return (ERROR);
		}
	}
	return (SUCCESS);
}
