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
		printf("%s `%s'\n", err.ctx1, err.ctx2);
	else if (err.type == T_CMD_NOT_FOUND)
		printf("%s: %s\n", err.ctx1, CMD_NOT_FOUND_MSG);
	else if (err.type == T_CMD_FOUND_NO_EXEC)
		printf("%s: %s\n", err.ctx1, CMD_FOUND_NOT_EXEC_MSG);
	else if (err.type == T_BAD_REQUEST_ERR)
		printf("%s: %s\n", err.ctx1, NO_FILE_OR_DIR_MSG);
	else if (err.type == T_BAD_REQUEST_ERR_PERM)
	{
		printf("%s: %s\n", err.ctx1, CMD_FOUND_NOT_EXEC_MSG);
		(*msh)->exit_code = T_BAD_REQUEST_ERR;
	}
	else if (err.type == T_INV_VARNAME)
	{
		printf("%s: %s\n", err.ctx1, err.ctx2);
		(*msh)->exit_code = 1;
	}
}

static void	handle_system_err(t_msh **msh, t_err err)
{
	(*msh)->exit_code = (int) errno;
	if (err.ctx1)
		perror(err.ctx1);
}

t_ret_err_val	print_err(t_msh **msh, t_err err, bool is_on_exit)
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
		exit((*msh)->exit_code);
	return ((t_ret_err_val){ERROR, NULL});
}
