/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathcmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:56:07 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/15 11:56:08 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cleanup(int ret_val, char **env_path, char **cmd_path)
{
	if (*env_path)
		free(*env_path);
	if (*cmd_path)
		free(*cmd_path);
	return (ret_val);
}

static char	*create_cmd_path_str(char *cmd_dir, char *cmd_name)
{
	char	*temp;
	char	*cmd_path;

	temp = ft_strjoin(cmd_dir, "/");
	if (!temp)
		return (NULL);
	cmd_path = ft_strjoin(temp, cmd_name);
	free(temp);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

// TODO handle what if cmd is not found in builtins
void	exec_path_cmd(char **argv)
{
	char	*env_path;
	char	*cmd_dir;
	char	*cmd_path;

	env_path = ft_strdup(getenv("PATH"));
	if (!env_path)
		handle_exit(true);
	cmd_dir = ft_strtok(env_path, ":");
	while (cmd_dir)
	{
		cmd_path = create_cmd_path_str(cmd_dir, argv[0]);
		if (!cmd_path)
			handle_exit(cleanup(true, &env_path, NULL));
		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, argv, NULL);
			handle_exit(cleanup(false, &env_path, &cmd_path));
		}
		free(cmd_path);
		cmd_dir = ft_strtok(NULL, ":");
	}
	free(env_path);
}
