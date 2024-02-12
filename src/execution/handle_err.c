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

int	handle_err(int res, t_err err, int is_on_exit)
{
	if (res == ERROR)
	{
		ft_putstr_fd(NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (err.type == SYNTAX_ERR)
		{
			ft_putstr_fd(SYNTAX_ERROR_MSG, STDERR_FILENO);
			ft_putstr_fd(err.context1, STDERR_FILENO);
			exit(SYNTAX_ERR);
		}
		if (err.type == CMD_NOT_FOUND)
		{
			ft_putstr_fd(CMD_NOT_FOUND_MSG, STDERR_FILENO);
			exit(CMD_NOT_FOUND);
		}
		else
			perror(err.context2);
		if (is_on_exit)
			exit(errno);
	}
	return (res);
}
