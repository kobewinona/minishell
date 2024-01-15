/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:43:14 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/12 11:14:56 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_exec *exec_cmd)
{
	if (ft_strncmp(exec_cmd->argv[0], "cd", 2) != 0)
	{
		if (ft_strncmp(exec_cmd->argv[0], "echo", 4) == 0)
			echo(exec_cmd->argv);
		else
			exec_ext_cmd(exec_cmd->argv);
	}
}
