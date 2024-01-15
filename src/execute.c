/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:43:14 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/12 11:14:56 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	exec_path_cmd(char **argv)
//{
//	char	*path;
//	char	*path_cp;
//
//	path = getenv("PATH");
//	path_cp = ft_strdup(path);
//}

//static int	exec_path_cmd(char **argv)
//{
//	char	*path = getenv("PATH");
//	char	*path_copy = ft_strdup(path);
//	char	*dir = strtok(path_copy, ":");
//	char	full_path[256];
//
//	while (dir != NULL)
//	{
//		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
//		if (access(full_path, X_OK) == 0)
//		{
//			pid_t pid = fork();
//			if (pid == 0)
//			{
//				char *argv[] = {full_path, NULL};
//				execve(full_path, argv, NULL);
//				exit(EXIT_FAILURE);
//			}
//			else if (pid > 0)
//			{
//				wait(NULL);
//				break ;
//			}
//			else
//			{
//				perror("fork error: ");
//				break ;
//			}
//		}
//		dir = strtok(NULL, ":");
//	}
//	free(path_copy);
//	return (SUCCESS);
//}

//void	exec_cmd(t_cmd *cmd)
//{
//	char	*cmd_name;
//
//	cmd_name = cmd->exec->argv[0];
//	if (ft_strncmp(cmd_name, "echo", ft_strlen("echo")) == 0)
//		echo(cmd->exec->argv[1]);
//	else
//	{
//		if (exec_path_cmd(cmd->exec->argv) == ERROR)
//			handle_exit(true);
//	}
//}
