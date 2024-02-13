/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:19:07 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/18 01:19:07 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_parsing_err(t_err err, bool is_on_exit)
{
	int	org_fd;

	org_fd = handle_err(dup(STDOUT_FILENO),
			(t_err){T_SYS_ERR, DUP}, true);
	handle_err(dup2(STDERR_FILENO, STDOUT_FILENO),
		(t_err){T_SYS_ERR, DUP2}, true);
	if (err.type == T_SYNTAX_ERR)
		printf("%s: %s `%s'\n", PRG_NAME, err.ctx1, err.ctx2);
	if (err.type == T_CMD_NOT_FOUND)
		printf("%s: %s: %s\n", PRG_NAME, err.ctx1, CMD_NOT_FOUND_MSG);
	handle_err(dup2(STDOUT_FILENO, STDERR_FILENO),
		(t_err){T_SYS_ERR, DUP2}, true);
	close(org_fd);
	if (is_on_exit)
		exit(err.type);
}

int	handle_err(int res, t_err err, bool is_on_exit)
{
	if (res == ERROR)
	{
		if (err.type == T_SYS_ERR)
		{
			ft_putstr_fd(PRG_NAME, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			perror(err.ctx2);
			if (is_on_exit)
				exit(errno);
		}
		handle_parsing_err(err, is_on_exit);
	}
	return (res);
}
