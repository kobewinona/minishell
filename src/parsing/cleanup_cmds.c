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

void	cleanup_cmds(t_cmd *cmd)
{
	int	i;

	if (cmd->type == T_EXEC)
	{
		i = 0;
		while (cmd->exec.argv[i])
			free(cmd->exec.argv[i++]);
	}
	if (cmd->type == T_PIPE)
	{
		cleanup_cmds(cmd->pipe.from);
		cleanup_cmds(cmd->pipe.to);
	}
	if (cmd->type == T_REDIR)
		cleanup_cmds(cmd->redir.subcmd);
	free(cmd);
	cmd = NULL;
}
