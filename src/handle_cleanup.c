/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:21:26 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/22 04:18:03 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_env_list(t_env *env_vars)
{
	t_env	*curr;
	t_env	*next;

	curr = env_vars;
	while (curr)
	{
		next = curr->next;
		free(curr->name);
		free(curr->value);
		free(curr);
		curr = next;
	}
}

void	cleanup_cmds(t_cmd **cmd)
{
	if (!(*cmd))
		return ;
	if ((*cmd)->type == C_PIPE)
	{
		cleanup_cmds(&(*cmd)->pipe.from);
		cleanup_cmds(&(*cmd)->pipe.to);
	}
	if ((*cmd)->type == C_REDIR)
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

void	cleanup(t_msh **msh)
{
	cleanup_env_list((*msh)->env_vars);
	cleanup_cmds(&(*msh)->cmd);
	free((*msh)->input);
	free((*msh));
	rl_clear_history();
}
