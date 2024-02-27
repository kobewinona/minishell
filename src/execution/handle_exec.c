/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:11:26 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/22 21:49:28 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exec(t_msh **msh, t_exec *cmd)
{
	if (cmd->argv[0])
	{
		if (!ft_strncmp(cmd->argv[0], ECHO, ft_strlen(ECHO)))
			echo(cmd->argv, (*msh)->env_vars);
		else if (!ft_strncmp(cmd->argv[0], CD, ft_strlen(CD)))
			return (SUCCESS);
		else if (!ft_strncmp(cmd->argv[0], PWD, ft_strlen(PWD)))
			pwd((*msh)->env_vars);
		else if (!ft_strncmp(cmd->argv[0], EXPORT, ft_strlen(EXPORT)))
			export(cmd->argv, (*msh)->env_vars);
		else if (!ft_strncmp(cmd->argv[0], UNSET, ft_strlen(UNSET)))
			unset(cmd->argv, (*msh)->env_vars);
		else if (!ft_strncmp(cmd->argv[0], EXIT, ft_strlen(EXIT)))
			exit_cmd(cmd->argv);
		else if (!ft_strncmp(cmd->argv[0], ENV, ft_strlen(ENV)))
			env_cmd(cmd->argv, (*msh)->env_vars);
		else
		{
			if (handle_err(fork(), msh, T_SYS_ERR, FORK, NULL) == 0)
				handle_ext_cmd(msh, cmd->argv);
			wait(NULL);
		}
	}
	return (SUCCESS);
}
