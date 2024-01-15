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
		exec_cmd(cmd->exec->argv);
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

int	main(void)
{
	char	*input;

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
		if (fork() == 0)
			run_cmd(parse_cmd(input));
		free(input);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}
