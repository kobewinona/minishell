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


void	collect_exit_code(t_msh **msh, int ext_code_encoded)
{
	if (WIFEXITED(ext_code_encoded))
	{
		(*msh)->exit_code = WEXITSTATUS(ext_code_encoded);
	}
	else if (WIFSIGNALED(ext_code_encoded))
	{
		(*msh)->exit_code = 128 + WTERMSIG(ext_code_encoded);
	}
}

//in case of invalid options for builtins
// need to return 2

int	handle_exec(t_msh **msh, t_exec *cmd)
{
	int	ext_code;

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
			if ((*msh)->child_pid != 0)
			{
				(*msh)->child_pid = fork();
				if ((*msh)->child_pid == ERROR)
					return (print_err(msh, (t_err){T_SYS_ERR, FORK}, false).t_int);
				if ((*msh)->child_pid == 0)
				{	
					track_signals(false);
					handle_ext_cmd(msh, cmd->argv);
				}
				waitpid((*msh)->child_pid, &ext_code, 0);
				//(*msh)->exit_code = WEXITSTATUS(ext_code);
				collect_exit_code(msh, ext_code);
			}
			else
				handle_ext_cmd(msh, cmd->argv);
		}
	}
	return ((*msh)->exit_code);
}
