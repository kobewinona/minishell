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

static void	run_cmd(t_cmd *cmd)
{
	if (cmd->type == EXEC)
		exec(cmd->exec);
}

static t_cmd	*construct_exec_cmd(char **argv)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		handle_exit(true);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->exec = (t_exec *)malloc(sizeof(t_exec));
	if (!cmd->exec)
	{
		free(cmd);
		handle_exit(true);
	}
	ft_memset(cmd->exec, 0, sizeof(t_cmd));
	cmd->type = EXEC;
	cmd->exec->argv = argv;
	return (cmd);
}

static t_cmd	*parse_cmd(char *input)
{
	return (construct_exec_cmd(ft_split(input, ' ')));
}

char **my_autocompletion(const char *text, int start, int end)
{
	char **matches;
	static char *current_directory; // Initialize with root directory
	static DIR *dir = NULL;
	int num_matches;
	struct dirent *entry;

	matches = NULL;
	if (!current_directory)
		current_directory = "./";
	printf("\ncurrent_directory %s\n", current_directory);
	dir = opendir(current_directory); // Open the current directory
//	printf("here 1\n");
	if (!dir)
		return NULL;
//	printf("here 2\n");
	num_matches = 0;
	entry = readdir(dir);
//	printf("here 3\n");
	if (entry)
		printf("\nentry exists\n");
	else
		printf("\nentry doesn't exists\n");
	while (entry)
	{
		printf("\ntext %s", text);
		char *filename = ft_strrchr(text, '/');
		if (filename)
			filename++; // Move past the '/'
		else
			filename = text;
		printf("\nfilename %s", filename);
//		printf("here 4\n");
		printf("\nentry->d_name %s", entry->d_name);
//		printf("\ntext %s, query %s", text, query);
		if (ft_strncmp(filename, entry->d_name, ft_strlen(filename)) == 0)
		{
//			printf("here 9\n");
			printf("\n --> matched entry %s", entry->d_name);
			char current_path[PATH_MAX];
			snprintf(current_path, sizeof(current_path), "%s", entry->d_name);
			struct stat st;
			printf("\ncurrent_path %s", current_path);
			stat(current_path, &st);
			printf("\nS_ISDIR(st.st_mode) %d\n", S_ISDIR(st.st_mode));
			if (S_ISDIR(st.st_mode))
			{
				// If it's a directory, append a '/' character
				printf("S_ISDIR(st.st_mode) is %d so we do what we do...\n", S_ISDIR(st.st_mode));
				matches = (char **)realloc(matches, (num_matches + 2) * sizeof(char *));
				matches[num_matches] = (char *)malloc(strlen(entry->d_name) + 2); // +2 for '/' and null terminator
				snprintf(matches[num_matches], strlen(entry->d_name) + 2, "%s/", entry->d_name);
				matches[num_matches + 1] = NULL;
			}
			else
			{
				// If it's not a directory, add it as is
				matches = (char **)realloc(matches, (num_matches + 2) * sizeof(char *));
				matches[num_matches] = (char *)malloc(strlen(entry->d_name) + 2); // +2 for ' ' and null terminator
				snprintf(matches[num_matches], strlen(entry->d_name) + 2, "%s ", entry->d_name);
				matches[num_matches + 1] = NULL;
			}
			int i = 0;
			while (matches[i])
			{
				if (ft_strncmp(matches[i], entry->d_name, ft_strlen(entry->d_name)) == 0)
				{
					current_directory = ft_strjoin(current_directory, matches[i]);
				}
				i++;
			}
			num_matches++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (matches);
}

int	main(void)
{
	char	*input;

	rl_attempted_completion_function = my_autocompletion;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (input[0] == 'c' && input[1] == 'd')
			cd(ft_split(input, ' '));
		if (fork() == 0)
			run_cmd(parse_cmd(input));
		free(input);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}
