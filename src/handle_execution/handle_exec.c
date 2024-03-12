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

static void	exec_ext_cmd(t_msh **msh, char *cmd_path, char **argv)
{
	if (access(cmd_path, X_OK) == SUCCESS)
	{
		execve(cmd_path, argv, envlist_to_arr((*msh)->env_vars));
		handle_err(msh, (t_err){T_SYS_ERR, argv[0], argv[1]}, true);
	}
	free(cmd_path);
	cmd_path = NULL;
}

static char	*create_cmd_path_str(t_msh **msh, char *cmd_dir, char *cmd_name)
{
	char	*temp;
	char	*cmd_path;

	temp = NULL;
	temp = ft_strjoin(cmd_dir, "/");
	if (!temp)
		return (handle_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_null);
	cmd_path = ft_strjoin(temp, cmd_name);
	free(temp);
	if (!cmd_path)
		return (handle_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_null);
	return (cmd_path);
}

static int	get_cmd_path(t_msh **msh, char **cmd_path, char **argv)
{
	char	*env_path;
	char	*cmd_dir;

	if (!access(argv[0], F_OK) && access(argv[0], X_OK))
		return (handle_err(msh, (t_err){
				T_CMD_FOUND_NO_EXEC, argv[0]}, false).t_int);
	env_path = get_env_var((*msh)->env_vars, "PATH");
	if (!env_path)
		handle_err(msh, (t_err){T_CMD_NOT_FOUND, argv[0]}, true);
	cmd_dir = ft_strtok(env_path, ":");
	while (cmd_dir)
	{
		(*cmd_path) = create_cmd_path_str(msh, cmd_dir, argv[0]);
		if (!(*cmd_path))
			return (handle_err(msh, (t_err){T_SYS_ERR,
					argv[0], argv[1]}, false).t_int);
		if (access((*cmd_path), X_OK) == SUCCESS)
			return (SUCCESS);
		cmd_dir = ft_strtok(NULL, ":");
	}
	handle_err(msh, (t_err){T_CMD_NOT_FOUND, argv[0]}, true);
}

void	handle_exec_ext_cmd(t_msh **msh, char **argv)
{
	int		ext_code;
	char	*cmd_path;

	ext_code = 0;
	if ((*msh)->child_pid != 0)
	{
		(*msh)->child_pid = fork2(msh);
		if ((*msh)->child_pid == ERROR)
			return ((void) handle_err(msh, (t_err){T_SYS_ERR, FORK}, false));
		if ((*msh)->child_pid == 0)
		{
			if (access(argv[0], F_OK | X_OK) == SUCCESS)
			{
				exec_ext_cmd(msh, argv[0], argv);
				return ;
			}
			if (get_cmd_path(msh, &cmd_path, argv) == ERROR)
				return ;
			exec_ext_cmd(msh, cmd_path, argv);
		}
		waitpid((*msh)->child_pid, &ext_code, 0);
		collect_exit_code(msh, ext_code);
	}
	else
	{
		if (get_cmd_path(msh, &cmd_path, argv) == ERROR)
			return ;
		exec_ext_cmd(msh, cmd_path, argv);
	}
}

int	handle_exec(t_msh **msh, t_exec *cmd)
{
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
			handle_exec_ext_cmd(msh, cmd->argv);
	}
	return ((*msh)->exit_code);
}
