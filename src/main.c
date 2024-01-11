/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:24:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/10 14:24:21 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quit(int is_on_error)
{
	if (is_on_error == false)
		exit(EXIT_SUCCESS);
	perror(NULL);
	exit(EXIT_FAILURE);
}

void	execute_command(const char *command)
{
	char *path = getenv("PATH");
	char *path_copy = ft_strdup(path);  // Duplicate PATH to avoid modifying the original
	char *dir = strtok(path_copy, ":");
	char full_path[256];

	while (dir != NULL) {
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0) {
			// Found the executable
			pid_t pid = fork();
			if (pid == 0) {
				// Child process
				char *argv[] = {full_path, NULL};
				execve(full_path, argv, NULL);
				exit(EXIT_FAILURE); // execve only returns on error
			} else if (pid > 0) {
				// Parent process
				wait(NULL); // Wait for the child process to finish
				break;
			} else {
				// Fork failed
				perror("fork");
				break;
			}
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
}

static void	run_cmd(t_cmd *cmd)
{
	if (cmd->type == EXEC)
		execute_command(cmd->exec->argv[0]);
}

static t_cmd	*construct_exec(char **argv)
{
	t_cmd	*cmd;
	t_exec	*exec;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		quit(true);
	ft_memset(cmd, 0, sizeof(t_cmd));
	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
	{
		free(cmd);
		quit(true);
	}
	ft_memset(exec, 0, sizeof(t_cmd));
	exec->argv = argv;
	cmd->type = EXEC;
	cmd->exec = exec;
	return (cmd);
}

static t_cmd	*parse_cmd(char **input)
{
	return (construct_exec(input));
}

int	main(void)
{
	char	*input;
	char	**argv;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		argv = ft_split(input, ' ');
		if (fork() == 0)
			run_cmd(parse_cmd(argv));
		free(input);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}
