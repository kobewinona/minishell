/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:19:07 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/19 11:29:17 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_other_err(t_msh **msh, t_err err)
{
	(*msh)->exit_code = err.type;
	if (err.type == T_OTHER_ERR)
	{
		printf("strerror %s\n", strerror(2));
		if (!ft_strncmp(err.ctx1, SYNTAX_ERR_MSG, ft_strlen(SYNTAX_ERR_MSG)))
			return ((void)printf("%s: %s\n", err.ctx1, err.ctx2));
		if (err.ctx2)
			return ((void)printf("%s `%s'\n", err.ctx1, err.ctx2));
		printf("%s\n", err.ctx1);
	}
	if (err.type == T_CMD_NOT_FOUND)
		printf("'%s': %s\n", err.ctx1, CMD_NOT_FOUND_MSG);
	if (err.type == T_CMD_NOT_EXECUTABLE)
		printf("%s: %s\n", err.ctx1, err.ctx2);
	if (err.type == T_BAD_REQUEST_ERR)
	{
		if (!ft_strncmp(err.ctx1, EXPORT, ft_strlen(EXPORT)))
			return ((void)printf("%s `%s': %s\n",
					err.ctx1, err.ctx2, EXPORT_INVALID_ARG_MSG1));
		printf("%s: %s\n", err.ctx1, err.ctx2);
	}
}

static void	handle_system_err(t_msh **msh, t_err err)
{
	(*msh)->exit_code = errno;
	if (err.ctx1)
		perror(err.ctx1);
}

void	handle_err(t_msh **msh, t_err err, bool is_on_exit)
{
	int	org_fd;
	int	exit_code;

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
		exit_code = (*msh)->exit_code;
		cleanup(msh);
		exit(exit_code);
	}
}
