/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ext_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:49:12 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/15 18:05:27 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_cmd_path_str(char *cmd_dir, char *cmd_name)
{
	char	*temp;
	char	*cmd_path;

	temp = NULL;
	cmd_path = NULL;
	temp = ft_strjoin(cmd_dir, "/");
	if (!temp)
		return (NULL);
	cmd_path = ft_strjoin(temp, cmd_name);
	free(temp);
	return (cmd_path);
}

static int	exec_ext_cmd(t_msh **msh, char *cmd_dir, char **env_path, char **argv)
{
	char		*cmd_path;

	cmd_path = NULL;
	cmd_path = create_cmd_path_str(cmd_dir, argv[0]);
	if (!cmd_path)
	{
		log_err(msh, T_SYS_ERR, argv[0], argv[1]);
		return (ERROR);
	}
	if (access(cmd_path, X_OK) == SUCCESS)
	{
		free(*env_path);
		execve(cmd_path, argv, envlist_to_arr((*msh)->env_vars));
		log_err(msh, T_SYS_ERR, argv[0], argv[1]);
		process_err(msh, true);
	}
	free(cmd_path);
	cmd_path = NULL;
	return (SUCCESS);
}



void	handle_ext_cmd(t_msh **msh, char **argv)
{
	char		*env_path;
	char		*cmd_dir;

	env_path = get_env_var((*msh)->env_vars, "PATH");
	if (!access(argv[0], F_OK | X_OK))
	{
		execve(argv[0], argv, envlist_to_arr((*msh)->env_vars));
		log_err(msh, T_SYS_ERR, argv[0], NULL);
		process_err(msh, true);
	}
	if (!env_path)
	{
		log_err(msh, T_CMD_NOT_FOUND, argv[0], NULL);
		process_err(msh, true);
	}
	cmd_dir = ft_strtok(env_path, ":");
	while (cmd_dir)
	{
		if (exec_ext_cmd(msh, cmd_dir, &env_path, argv) == ERROR)
			break ;
		cmd_dir = ft_strtok(NULL, ":");
	}
	free(env_path);
	log_err(msh, T_CMD_NOT_FOUND, argv[0], NULL);
	process_err(msh, true);
}
