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

static void	exec_ext_cmd(char *cmd_dir, char **env_path, char **argv)
{
	extern char	**environ;
	char		*cmd_path;

	cmd_path = NULL;
	cmd_path = create_cmd_path_str(cmd_dir, argv[0]);
	if (!cmd_path)
		handle_err(ERROR, (t_err){T_SYS_ERR, argv[0], argv[1]}, true);
	if (access(cmd_path, X_OK) == 0)
	{
		free(*env_path);
		execve(cmd_path, argv, environ);
		handle_err(ERROR, (t_err){T_SYS_ERR, argv[0], argv[1]}, false);
	}
	free(cmd_path);
	cmd_path = NULL;
}



void	handle_ext_cmd(char **argv, t_var_node *env_vars)
{
	char		*env_path;
	char		*cmd_dir;

	env_path = get_env_var(env_vars, "PATH");
	if (env_path == NULL && (access(argv[0], F_OK | X_OK) == -1)) // PATH deleted and executable not found locally
		handle_err(ERROR, (t_err){T_CMD_NOT_FOUND, argv[0]}, true);
	if (access(argv[0], F_OK | X_OK) == 0)
	{
		execve(argv[0], argv, NULL); //will need to pass env from our list too
		handle_err(ERROR, (t_err){T_SYS_ERR, argv[0], argv[1]}, false);
	}
	env_path = ft_strdup(get_env_var(env_vars,"PATH"));
	if (!env_path)
		handle_err(ERROR, (t_err){T_SYS_ERR, argv[0], MALLOC}, true);
	cmd_dir = ft_strtok(env_path, ":");
	while (cmd_dir)
	{
		exec_ext_cmd(cmd_dir, &env_path, argv);
		cmd_dir = ft_strtok(NULL, ":");
	}
	free(env_path);
	handle_err(ERROR, (t_err){T_CMD_NOT_FOUND, argv[0]}, true);
}
