/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:32:32 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/15 12:32:33 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cleanup(int exit_status, char **env_path, char **cmd_path)
{
	if (*env_path)
		free(*env_path);
	if (*cmd_path)
		free(*cmd_path);
	return (exit_status);
}

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

// TODO handle what if cmd is not found in builtins
void	exec_ext_cmd(char **argv)
{
	extern char	**environ;
	char		*env_path;
	char		*cmd_dir;
	char		*cmd_path;

	env_path = NULL;
	cmd_path = NULL;
	env_path = ft_strdup(getenv("PATH"));
	if (!env_path)
		handle_exit(EXIT_FAILURE);
	cmd_dir = ft_strtok(env_path, ":");
	while (cmd_dir)
	{
		cmd_path = create_cmd_path_str(cmd_dir, argv[0]);
		if (!cmd_path)
			handle_exit(cleanup(EXIT_FAILURE, &env_path, NULL));
		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, argv, environ);
			handle_exit(cleanup(EXIT_FAILURE, &env_path, &cmd_path));
		}
		free(cmd_path);
		cmd_dir = ft_strtok(NULL, ":");
	}
	handle_exit(cleanup(EXIT_FAILURE, &env_path, &cmd_path));
}
