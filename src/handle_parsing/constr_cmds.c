/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constr_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:09:19 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/27 14:16:24 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_cmd	*constr_cmd(t_msh **msh, t_types cmd_type)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (print_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_null);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->type = cmd_type;
	return (cmd);
}

t_cmd	*constr_exec_cmd(t_msh **msh, char *input)
{
	t_cmd	*cmd;

	cmd = constr_cmd(msh, T_EXEC);
	if (!cmd)
		return (NULL);
	ft_memset(cmd->exec.argv, 0, sizeof(char *));
	if (populate_argv(msh, cmd->exec.argv, input) == ERROR)
		return (cleanup_cmds(&cmd));
	return (cmd);
}

t_cmd	*constr_redir_cmd(t_msh **msh, t_types r_type, t_cmd *subcmd, char *f)
{
	t_cmd	*cmd;

	if (!f || !subcmd)
		return (NULL);
	cmd = constr_cmd(msh, T_REDIR);
	if (!cmd)
		return (cleanup_cmds(&subcmd));
	cmd->redir.type = r_type;
	cmd->redir.subcmd = subcmd;
	if (r_type == T_REDIR_STDOUT)
		cmd->redir.mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (r_type == T_APPEND_STDOUT)
		cmd->redir.mode = O_WRONLY | O_APPEND | O_CREAT;
	if (r_type == T_REDIR_STDIN || r_type == T_HEREDOC)
		cmd->redir.mode = O_RDONLY;
	cmd->redir.f = f;
	return (cmd);
}

t_cmd	*constr_pipe_cmd(t_msh **msh, t_cmd *cmd1, t_cmd *cmd2)
{
	t_cmd	*cmd;

	if (!cmd1)
	{
		if (cmd2)
			cleanup_cmds(&cmd2);
		return (NULL);
	}
	if (!cmd2)
		return (cleanup_cmds(&cmd1));
	cmd = constr_cmd(msh, T_PIPE);
	if (!cmd)
		return (NULL);
	cmd->pipe.from = cmd1;
	cmd->pipe.to = cmd2;
	return (cmd);
}
