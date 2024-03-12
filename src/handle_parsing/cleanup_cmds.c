/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:19:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/22 23:19:17 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	cleanup_exec_cmd(t_cmd **cmd)
// {
// 	int	i;

// 	i = 0;
// 	while ((*cmd)->exec.argv[i])
// 	{
// 		free((*cmd)->exec.argv[i]);
// 		(*cmd)->exec.argv[i] = NULL;
// 		i++;
// 	}
// }

static void	cleanup_redir_cmd(t_cmd **cmd)
{
	if ((*cmd)->redir.fd[0] > 2)
		close((*cmd)->redir.fd[0]);
	if ((*cmd)->redir.fd[1] > 2)
		close((*cmd)->redir.fd[1]);
	if ((*cmd)->redir.f)
		free((*cmd)->redir.f);
}

void	cleanup_cmds(t_cmd **cmd)
{
	if (!(*cmd))
		return ;
	// if ((*cmd)->type == T_EXEC)
	// 	cleanup_exec_cmd(cmd);
	if ((*cmd)->type == T_PIPE)
	{
		cleanup_cmds(&(*cmd)->pipe.from);
		cleanup_cmds(&(*cmd)->pipe.to);
	}
	if ((*cmd)->type == T_REDIR)
	{
		cleanup_redir_cmd(cmd);
		cleanup_cmds(&(*cmd)->redir.subcmd);
	}
	free((*cmd));
	(*cmd) = NULL;
}
