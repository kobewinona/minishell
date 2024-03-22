/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constr_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:09:19 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/22 04:18:48 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*constr_cmd(t_msh **msh, t_cmd_t type)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (handle_err(msh, SYSTEM, MALLOC, 1), NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->type = type;
	return (cmd);
}

int	populate_argv(t_msh **msh, char **argv, char *input)
{
	int	index;

	if (!argv || !input)
		return (ERROR);
	index = 0;
	while (argv[index])
		index++;
	while (!is_emptystr(input))
	{
		argv[index] = get_value(msh, &input);
		if (!argv[index])
			return (ERROR);
		if (!argv[index])
			return (handle_err(msh, SYSTEM, MALLOC, 1), ERROR);
		index++;
	}
	return (SUCCESS);
}

t_cmd	*constr_exec_cmd(t_msh **msh, char *input)
{
	t_cmd	*cmd;

	cmd = constr_cmd(msh, C_EXEC);
	if (!cmd)
		return (NULL);
	ft_memset(cmd->exec.argv, 0, sizeof(char *));
	if (populate_argv(msh, cmd->exec.argv, input) == ERROR)
		return (cleanup_cmds(&cmd), NULL);
	return (cmd);
}

t_cmd	*constr_redir_cmd(t_msh **msh, t_redir_t type, t_cmd *subcmd, char *f)
{
	t_cmd	*cmd;

	if (!f || !subcmd)
		return (NULL);
	cmd = constr_cmd(msh, C_REDIR);
	if (!cmd)
		return (cleanup_cmds(&subcmd), NULL);
	cmd->redir.type = type;
	cmd->redir.subcmd = subcmd;
	if (type == R_STDOUT)
		cmd->redir.mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (type == R_APPEND)
		cmd->redir.mode = O_WRONLY | O_APPEND | O_CREAT;
	if (type == R_STDIN || type == R_HEREDOC)
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
		return (cleanup_cmds(&cmd1), NULL);
	cmd = constr_cmd(msh, C_PIPE);
	if (!cmd)
		return (NULL);
	cmd->pipe.from = cmd1;
	cmd->pipe.to = cmd2;
	return (cmd);
}
