/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:11:26 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 11:20:37 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_cmd_path_str(t_msh **msh, char *env_path, char *cmd_name)
{
	char	*cmd_path;
	char	*cmd_dir;
	char	*temp;

	cmd_path = NULL;
	temp = NULL;
	cmd_dir = ft_strtok(env_path, ":");
	while (cmd_dir)
	{
		temp = ft_strjoin(cmd_dir, "/");
		cmd_path = ft_strjoin(temp, cmd_name);
		if (!cmd_path)
			return (handle_err(msh, SYSTEM, MALLOC, 1), NULL);
		free(temp);
		if (access(cmd_path, X_OK) == SUCCESS)
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
		cmd_dir = ft_strtok(NULL, ":");
	}
	return (NULL);
}

static void	get_cmd_path(t_msh **msh, char **cmd_path, char **argv)
{
	struct stat	path_stat;
	char		*env_path;

	if (is_emptystr(argv[0]))
		handle_err(msh, CMD_NOT_FOUND, argv[0], 127);
	if (stat(argv[0], &path_stat) == SUCCESS)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (handle_err(msh, CMD_IS_DIR, argv[0], 126));
	}
	if (access(argv[0], F_OK | X_OK) == SUCCESS)
	{
		(*cmd_path) = argv[0];
		return ;
	}
	env_path = get_env_var((*msh)->env_vars, "PATH");
	if (!env_path)
		handle_err(msh, CMD_NOT_FOUND, argv[0], 127);
	(*cmd_path) = create_cmd_path_str(msh, env_path, argv[0]);
	if ((*cmd_path) == NULL)
		handle_err(msh, CMD_NOT_FOUND, argv[0], 127);
}

static void	exec_ext_cmd(t_msh **msh, char **argv)
{
	char		*cmd_path;

	get_cmd_path(msh, &cmd_path, argv);
	if (access(cmd_path, X_OK) == SUCCESS)
	{
		execve(cmd_path, argv, envlist_to_arr((*msh)->env_vars));
		free(cmd_path);
		cmd_path = NULL;
		handle_err(msh, SYSTEM, argv[0], 2);
	}
	free(cmd_path);
	cmd_path = NULL;
	handle_err(msh, SYSTEM, argv[0], 1);
}

void	handle_exec_ext_cmd(t_msh **msh, char **argv)
{
	int		exit_code;

	g_state = IS_EXEC;
	exit_code = 0;
	if ((*msh)->curr_pid != 0)
	{
		(*msh)->curr_pid = fork();
		if ((*msh)->curr_pid == ERROR)
			return (handle_err(msh, SYSTEM, FORK, 1));
		if ((*msh)->curr_pid == 0)
		{
			if (setup_signal(SIGINT, SIG_DFL) == ERROR)
				handle_exit(msh, EXIT_FAILURE, true);
			exec_ext_cmd(msh, argv);
		}
		waitpid((*msh)->curr_pid, &exit_code, 0);
		update_exit_code(msh, exit_code);
	}
	else
		exec_ext_cmd(msh, argv);
	g_state = IS_IDLE;
}

void	handle_exec(t_msh **msh, t_exec *cmd)
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
}
