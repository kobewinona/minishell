/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:11:26 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/16 16:11:27 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exec(t_exec *cmd)
{
	if (cmd->argv[0])
	{
		if (!ft_strncmp(cmd->argv[0], ECHO, ft_strlen(ECHO)))
			echo(cmd->argv, cmd->env_vars);
		else if (!ft_strncmp(cmd->argv[0], CD, ft_strlen(CD)))
			return ;
		else if (!ft_strncmp(cmd->argv[0], PWD, ft_strlen(PWD)))
			pwd(cmd->env_vars);
		else if (!ft_strncmp(cmd->argv[0], EXPORT, ft_strlen(EXPORT)))
			export(cmd->argv, cmd->env_vars);
		else if (!ft_strncmp(cmd->argv[0], UNSET, ft_strlen(UNSET)))
			unset(cmd->argv, cmd->env_vars);
		else if (!ft_strncmp(cmd->argv[0], EXIT, ft_strlen(EXIT)))
			exit_cmd(cmd->argv);
		else if (!ft_strncmp(cmd->argv[0], ENV, ft_strlen(ENV)))
			env_cmd(cmd->argv, env_vars);
		else
		{
			if (!handle_err(fork(), (t_err){T_SYS_ERR, FORK}, true))
				handle_ext_cmd(cmd->argv, cmd->env_vars);
			wait(NULL);
		}
	}
}
