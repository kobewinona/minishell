/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ext_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:49:12 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/16 23:49:13 by dklimkin         ###   ########.fr       */
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

static void	exec_ext_cmd(char *cmd_dir, char **env_path, char **argv)
{
	extern char	**environ;
	char		*cmd_path;

	cmd_path = NULL;
	cmd_path = create_cmd_path_str(cmd_dir, argv[0]);
	if (!cmd_path)
		handle_error(ERROR, argv[0], argv[1], true);
	if (access(cmd_path, X_OK) == 0)
	{
		free(*env_path);
		execve(cmd_path, argv, environ);
		handle_error(ERROR, argv[0], argv[1], false);
	}
	free(cmd_path);
	cmd_path = NULL;
}

void	handle_ext_cmd(char **argv)
{
	char		*env_path;
	char		*cmd_dir;

	env_path = NULL;
	env_path = ft_strdup(getenv("PATH"));
	if (!env_path)
		handle_error(ERROR, argv[0], MALLOC, true);
	cmd_dir = ft_strtok(env_path, ":");
	while (cmd_dir)
	{
		exec_ext_cmd(cmd_dir, &env_path, argv);
		cmd_dir = ft_strtok(NULL, ":");
	}
	free(env_path);
	handle_error(ERROR, argv[0], CMD_NOT_FOUND, true);
}
