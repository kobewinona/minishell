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


bool	is_builtin(t_exec *cmd)
{
	if (!ft_strncmp(cmd->argv[0], ECHO, ft_strlen(ECHO)))
		return (true);
	else if (!ft_strncmp(cmd->argv[0], CD, ft_strlen(CD)))
		return (true);
	else if (!ft_strncmp(cmd->argv[0], PWD, ft_strlen(PWD)))
		return (true);
	else if (!ft_strncmp(cmd->argv[0], EXPORT, ft_strlen(EXPORT)))
		return (true);
	else if (!ft_strncmp(cmd->argv[0], UNSET, ft_strlen(UNSET)))
		return (true);
	else if (!ft_strncmp(cmd->argv[0], EXIT, ft_strlen(EXIT)))
		return (true);
	else if (!ft_strncmp(cmd->argv[0], ENV, ft_strlen(ENV)))
		return (true);
	return (false);
}

//in case of invalid options for builtins
// need to return 2

int	handle_exec(t_msh **msh, t_exec *cmd)
{
	int ext_code;


	ext_code = 0;
	if (cmd->argv[0])
	{
		if (!ft_strncmp(cmd->argv[0], ECHO, 1000))
			echo(cmd->argv, msh);
		else if (!ft_strncmp(cmd->argv[0], CD, 1000))
			cd(cmd->argv[1], msh);
		else if (!ft_strncmp(cmd->argv[0], PWD, 1000))
			pwd(msh);
		else if (!ft_strncmp(cmd->argv[0], EXPORT, 1000))
			export(cmd->argv, msh);
		else if (!ft_strncmp(cmd->argv[0], UNSET, 1000))
			unset(cmd->argv, msh);
		else if (!ft_strncmp(cmd->argv[0], EXIT, 1000))
			exit_cmd(cmd->argv, msh);
		else if (!ft_strncmp(cmd->argv[0], ENV, 1000))
			env_cmd(cmd->argv, msh);

		else
		{
			if ((*msh)->is_parent)
			{
				if (handle_err(fork(), msh, T_SYS_ERR, FORK, NULL) == 0)
				{
					(*msh)->is_parent = false;
					handle_ext_cmd(msh, cmd->argv);
				}
				wait(&ext_code);
				(*msh)->exit_code = WEXITSTATUS(ext_code);
			}
			else
			{
				handle_ext_cmd(msh, cmd->argv);
			}
			
		}
		
	}
	if (!(*msh)->is_parent)
		exit((*msh)->exit_code);
	return ((*msh)->exit_code);
}
