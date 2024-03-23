/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:03:42 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/23 13:25:24 by dklimkin         ###   ########.fr       */
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

static int	handle_heredoc(t_msh **msh, t_redir *cmd)
{
	int		pipe_fds[2];
	char	*heredoct_input;

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

static char	*prepare_filename(t_msh **msh, char *f)
{
	char	*filename;

	if (f[0] == '$')
	{
		if (!is_in_env((*msh)->env_vars, &f[1]))
			return (handle_err(msh, AMBGIGUOUS_R, f, 1), NULL);
	}
	filename = ft_strdup(f);
	if (!filename)
		return (handle_err(msh, SYSTEM, MALLOC, 1), NULL);
	if (ft_strchr(f, '$'))
	{
		if (exp_env_vars(msh, &filename) == ERROR)
			return (free(filename), NULL);
	}
	return (filename);
}

static int	prepare_fd(t_msh **msh, t_redir *cmd)
{
	int		prepared_fd;
	char	*filename;

	if (cmd->type == R_HEREDOC)
		return (handle_heredoc(msh, cmd));
	filename = prepare_filename(msh, cmd->f);
	if (!filename)
		return (ERROR);
	prepared_fd = open(filename, cmd->mode, RW_R_R_PERM);
	free(filename);
	if (prepared_fd < 0)
		return (handle_err(msh, SYSTEM, cmd->f, 1), ERROR);
	return (prepared_fd);
}

void	prepare_fds(t_msh **msh, t_cmd **cmd)
{
	if (!(*cmd))
		return ;
	if ((*cmd)->type == C_PIPE)
	{
		prepare_fds(msh, &(*cmd)->pipe.from);
		prepare_fds(msh, &(*cmd)->pipe.to);
	}
	if ((*cmd)->type == C_REDIR)
	{
		(*cmd)->redir.fd[0] = prepare_fd(msh, &(*cmd)->redir);
		if ((*cmd)->redir.fd[0] == ERROR)
			return ;
		if ((*cmd)->redir.subcmd->type == C_REDIR)
			prepare_fds(msh, &(*cmd)->redir.subcmd);
	}
}
