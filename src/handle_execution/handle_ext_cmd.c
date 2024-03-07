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

static char	*create_cmd_path_str(t_msh **msh, char *cmd_dir, char *cmd_name)
{
	char	*temp;
	char	*cmd_path;

	temp = NULL;
	temp = ft_strjoin(cmd_dir, "/");
	if (!temp)
		return (print_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_null);
	cmd_path = ft_strjoin(temp, cmd_name);
	free(temp);
	if (!cmd_path)
		return (print_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_null);
	return (cmd_path);
}

static int	exec_ext_cmd(t_msh **msh, char *cmd_dir, char **argv)
{
	char		*cmd_path;

	if (is_emptystr(argv[0]))
		return (print_err(msh, (t_err){T_SYS_ERR,
				argv[0], argv[1]}, false).t_int);
	cmd_path = NULL;
	cmd_path = create_cmd_path_str(msh, cmd_dir, argv[0]);
	if (!cmd_path)
		return (print_err(msh, (t_err){T_SYS_ERR,
				argv[0], argv[1]}, false).t_int);
	if (access(cmd_path, X_OK) == SUCCESS)
	{
		execve(cmd_path, argv, envlist_to_arr((*msh)->env_vars));
		print_err(msh, (t_err){T_SYS_ERR, argv[0], argv[1]}, true);
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
	if (!access(argv[0], F_OK) && access(argv[0], X_OK))
		print_err(msh, (t_err){T_CMD_FOUND_NO_EXEC, argv[0]}, true);
	else if (!access(argv[0], F_OK | X_OK))
	{
		execve(argv[0], argv, envlist_to_arr((*msh)->env_vars));
		print_err(msh, (t_err){T_SYS_ERR, argv[0], argv[1]}, true);
	}
	if (!env_path)
		print_err(msh, (t_err){T_CMD_NOT_FOUND, argv[0]}, true);
	cmd_dir = ft_strtok(env_path, ":");
	while (cmd_dir)
	{
		if (exec_ext_cmd(msh, cmd_dir, argv) == ERROR)
			break ;
		cmd_dir = ft_strtok(NULL, ":");
	}
	print_err(msh, (t_err){T_CMD_NOT_FOUND, argv[0]}, true);
}
