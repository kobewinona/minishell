/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_constructs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:09:19 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/09 18:09:19 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*constr_cmd(t_types cmd_type)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		handle_err(ERROR, (t_err){T_SYS_ERR, NULL, MALLOC}, true);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->type = cmd_type;
	return (cmd);
}

t_cmd	*constr_exec_cmd(char *input)
{
	t_cmd	*cmd;
	char	**argv;

	cmd = constr_cmd(T_EXEC);
	cmd->exec = (t_exec *)malloc(sizeof(t_exec));
	if (!cmd->exec)
	{
		free(cmd);
		handle_err(ERROR, (t_err){T_SYS_ERR, argv[0], MALLOC}, true);
	}
	ft_memset(cmd->exec, 0, sizeof(t_cmd));
	cmd->exec->argv = parse_argv(input);
	return (cmd);
}

t_cmd	*constr_heredoc_cmd(t_cmd *subcmd, char *eof)
{
	t_cmd	*cmd;

	cmd = constr_cmd(T_HEREDOC);
	cmd->heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!cmd->heredoc)
	{
		free(cmd);
		handle_err(ERROR, (t_err){T_SYS_ERR, NULL, MALLOC}, true);
	}
	ft_memset(cmd->heredoc, 0, sizeof(t_heredoc));
	cmd->heredoc->subcmd = subcmd;
	cmd->heredoc->eof = eof;
	return (cmd);
}

t_cmd	*constr_redir_cmd(t_types redir_type, t_cmd *subcmd, char *file)
{
	t_cmd	*cmd;

	cmd = constr_cmd(T_REDIR);
	cmd->redir = (t_redir *)malloc(sizeof(t_redir));
	if (!cmd->redir)
	{
		free(cmd);
		handle_err(ERROR, (t_err){T_SYS_ERR, NULL, MALLOC}, true);
	}
	ft_memset(cmd->redir, 0, sizeof(t_redir));
	cmd->redir->type = redir_type;
	cmd->redir->subcmd = subcmd;
	cmd->redir->file = file;
	if (redir_type == T_REDIR_STDOUT)
		cmd->redir->mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (redir_type == T_REDIR_STDIN)
		cmd->redir->mode = O_RDONLY;
	if (redir_type == T_APPEND_STDOUT)
		cmd->redir->mode = O_WRONLY | O_APPEND | O_CREAT;
	return (cmd);
}

t_cmd	*constr_pipe_cmd(t_cmd *cmd1, t_cmd *cmd2)
{
	t_cmd	*cmd;

	if (!cmd1 || !cmd2)
		return (NULL);
	cmd = constr_cmd(T_PIPE);
	cmd->pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!cmd->pipe)
	{
		free(cmd);
		handle_err(ERROR, (t_err){T_SYS_ERR, NULL, MALLOC}, true);
	}
	ft_memset(cmd->pipe, 0, sizeof(t_cmd));
	cmd->pipe->from = cmd1;
	cmd->pipe->to = cmd2;
	return (cmd);
}
