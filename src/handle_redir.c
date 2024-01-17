/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:20:11 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/16 22:20:13 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*construct_redir_cmd(
		t_redir_type type, t_cmd *subcmd, char *file, int mode)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		handle_exit(EXIT_FAILURE);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->redir = (t_redir *)malloc(sizeof(t_redir));
	if (!cmd->redir)
	{
		free(cmd);
		handle_exit(EXIT_FAILURE);
	}
	ft_memset(cmd->redir, 0, sizeof(t_redir));
	cmd->type = REDIR;
	cmd->redir->type = type;
	cmd->redir->subcmd = subcmd;
	cmd->redir->file = file;
	cmd->redir->mode = mode;
	return (cmd);
}

void	handle_redir(t_redir *redir_params)
{
	int	org_stdout;
	int	new_fd;
	int	redir_fd;

	redir_fd = 1;
	new_fd = open(redir_params->file, redir_params->mode, RW_R_R_PERM);
	if (new_fd == ERROR)
		handle_exit(EXIT_FAILURE);
	if (redir_params->type == REDIR_STD_OUT)
		redir_fd = STDOUT_FILENO;
	if (redir_params->type == REDIR_STD_IN)
		redir_fd = STDIN_FILENO;
	org_stdout = dup(redir_fd);
	dup3(new_fd, redir_fd);
	run_cmd(redir_params->subcmd);
	close(new_fd);
	dup3(org_stdout, redir_fd);
	close(org_stdout);
	handle_exit(EXIT_SUCCESS);
}
