/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:14:37 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/17 20:14:38 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(int res, char *cmd, char *context, int is_on_exit)
{
	if (res == ERROR)
	{
		ft_putstr_fd(NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (cmd)
		{
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		if (!ft_strncmp(context, CMD_NOT_FOUND, ft_strlen(CMD_NOT_FOUND)))
			ft_putstr_fd(CMD_NOT_FOUND, STDERR_FILENO);
		else
			perror(context);
		if (is_on_exit)
			exit(errno);
	}
	return (res);
}
