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
		if (!ft_strncmp(cmd->argv[0], ECHO, ft_strlen(ECHO)))
			echo(cmd->argv, msh);
		else if (!ft_strncmp(cmd->argv[0], CD, ft_strlen(CD)))
			cd(cmd->argv[1], msh);
		else if (!ft_strncmp(cmd->argv[0], PWD, ft_strlen(PWD)))
			pwd(msh);
		else if (!ft_strncmp(cmd->argv[0], EXPORT, ft_strlen(EXPORT)))
			export(cmd->argv, msh);
		else if (!ft_strncmp(cmd->argv[0], UNSET, ft_strlen(UNSET)))
			unset(cmd->argv, msh);
		else if (!ft_strncmp(cmd->argv[0], EXIT, ft_strlen(EXIT)))
			exit_cmd(cmd->argv, msh);
		else if (!ft_strncmp(cmd->argv[0], ENV, ft_strlen(ENV)))
			env_cmd(cmd->argv, msh);

		else
		{
			if (handle_err(fork(), msh, T_SYS_ERR, FORK, NULL) == 0)
				handle_ext_cmd(msh, cmd->argv);
			wait(&ext_code);
			(*msh)->exit_code = WEXITSTATUS(ext_code);

		}
		
	}
	if (getpid() != (*msh)->ppid)
		exit((*msh)->exit_code);
	return ((*msh)->exit_code);
}
