/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:19:07 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/27 17:08:11 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_other_err(t_msh **msh, t_err err)
{
	(*msh)->exit_code = err.type;
	if (err.type == T_OTHER_ERR)
	{
		if (err.ctx2)
			return ((void)printf("%s `%s'\n", err.ctx1, err.ctx2));
		printf("%s\n", err.ctx1);
	}
	if (err.type == T_CMD_NOT_FOUND)
		printf("%s: %s\n", err.ctx1, CMD_NOT_FOUND_MSG);
	if (err.type == T_CMD_FOUND_NO_EXEC)
		printf("%s: %s\n", err.ctx1, CMD_FOUND_NOT_EXEC_MSG);
	if (err.type == T_BAD_REQUEST_ERR)
	{
		if (!ft_strncmp(err.ctx1, EXPORT, ft_strlen(EXPORT)))
			return ((void)printf("%s `%s': %s\n",
					err.ctx1, err.ctx2, EXPORT_INVALID_ARG_MSG1));
		if (err.ctx2)
			return ((void)printf("%s `%s'\n", err.ctx1, err.ctx2));
		printf("%s: %s\n", err.ctx1, NO_FILE_OR_DIR_MSG);
	}
}

static void	handle_system_err(t_msh **msh, t_err err)
{
	(*msh)->exit_code = errno;
	if (err.ctx1)
		perror(err.ctx1);
}

t_ret_err_val	handle_err(t_msh **msh, t_err err, bool is_on_exit)
{
	int	org_fd;

	ft_putstr_fd(PRG_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	org_fd = dup(STDOUT_FILENO);
	if (org_fd == ERROR)
		exit((*msh)->exit_code);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == ERROR)
		exit((*msh)->exit_code);
	if (err.type == T_SYS_ERR)
		handle_system_err(msh, err);
	else
		handle_other_err(msh, err);
	dup2(STDOUT_FILENO, STDERR_FILENO);
	close(org_fd);
	if (is_on_exit)
	{
		free_envlist((*msh)->env_vars);
		cleanup_cmds(&(*msh)->cmd);
		free((*msh));
		exit((*msh)->exit_code);
	}
	return ((t_ret_err_val){ERROR, NULL});
}
