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

t_cmd	*constr_exec_cmd(char *input, t_var_node *env_vars)
{
	t_cmd	*cmd;

	cmd = constr_cmd(T_EXEC);
	memset(cmd->exec.argv, 0, sizeof(cmd->exec.argv));
	populate_argv(cmd->exec.argv, input);
	cmd->exec.env_vars = env_vars;
	return (cmd);
}

static int	prepare_fd(t_types redir_type, int mode, char *f)
{
	int	ret_fd;
	int	pipe_fds[2];

	if (redir_type == T_HEREDOC) {
		handle_err(pipe(pipe_fds), (t_err){T_SYS_ERR, PIPE}, true);
		write(pipe_fds[1], f, strlen(f));
		close(pipe_fds[1]);
		ret_fd = pipe_fds[0];
		free(f);
	}
	else
		ret_fd = handle_err(open(f, mode, RW_R_R_PERM),
				(t_err){T_SYS_ERR, f}, true);
	return (ret_fd);
}

t_cmd	*constr_redir_cmd(t_types redir_type, t_cmd *subcmd, char *f)
{
	t_cmd	*cmd;

	cmd = constr_cmd(T_REDIR);
	cmd->redir.type = redir_type;
	cmd->redir.subcmd = subcmd;
	if (redir_type == T_REDIR_STDOUT)
		cmd->redir.mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (redir_type == T_APPEND_STDOUT)
		cmd->redir.mode = O_WRONLY | O_APPEND | O_CREAT;
	if (redir_type == T_REDIR_STDIN || redir_type == T_HEREDOC)
		cmd->redir.mode = O_RDONLY;
	cmd->redir.fd = prepare_fd(cmd->redir.type, cmd->redir.mode, f);
	return (cmd);
}

t_cmd	*constr_pipe_cmd(t_cmd *cmd1, t_cmd *cmd2)
{
	t_cmd	*cmd;

	if (!cmd1 || !cmd2)
		return (NULL);
	cmd = constr_cmd(T_PIPE);
	cmd->pipe.from = cmd1;
	cmd->pipe.to = cmd2;
	return (cmd);
}
