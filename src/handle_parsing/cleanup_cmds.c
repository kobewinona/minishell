/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:19:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 23:35:07 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_cmds(t_cmd **cmd)
{
	if (!(*cmd))
		return ;
	if ((*cmd)->type == T_PIPE)
	{
		cleanup_cmds(&(*cmd)->pipe.from);
		cleanup_cmds(&(*cmd)->pipe.to);
	}
	if ((*cmd)->type == T_REDIR)
	{
		if ((*cmd)->redir.fd[0] > 2)
			close((*cmd)->redir.fd[0]);
		if ((*cmd)->redir.fd[1] > 2)
			close((*cmd)->redir.fd[1]);
		cleanup_cmds(&(*cmd)->redir.subcmd);
	}
	free((*cmd));
	(*cmd) = NULL;
}
