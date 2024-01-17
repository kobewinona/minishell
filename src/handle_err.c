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

int	handle_err(int res, char *cxt1, char *cxt2, int is_on_exit)
{
	if (res == ERROR)
	{
		ft_putstr_fd(NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (cxt1)
		{
			ft_putstr_fd(cxt1, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		if (!ft_strncmp(cxt2, CMD_NOT_FOUND, ft_strlen(CMD_NOT_FOUND)))
			ft_putstr_fd(CMD_NOT_FOUND, STDERR_FILENO);
		else
			perror(cxt2);
		if (is_on_exit)
			exit(errno);
	}
	return (res);
}
