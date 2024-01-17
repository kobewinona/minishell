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

void	run_cmd(t_cmd *cmd)
{
	if (cmd->type == EXEC)
		handle_exec(cmd->exec);
	else if (cmd->type == PIPE)
		handle_pipe(cmd->pipe);
	else if (cmd->type == REDIR)
		handle_redir(cmd->redir);
	else
		handle_exit(EXIT_FAILURE);
}

static t_cmd	*parse_cmd(char *input)
{
	t_cmd	*exec_cmd1 = NULL;
	t_cmd	*exec_cmd2 = NULL;
	t_cmd	*exec_cmd3 = NULL;
	t_cmd	*pipe_cmd1 = NULL;
	t_cmd	*pipe_cmd2 = NULL;
	t_cmd	*redir_cmd1 = NULL;
	t_cmd	*redir_cmd2 = NULL;

	exec_cmd1 = construct_exec_cmd(ft_split(ft_strtok(input, "<"), ' '));
	printf("exec_cmd1 cmd name: %s\n", exec_cmd1->exec->argv[0]);
	redir_cmd1 = construct_redir_cmd(REDIR_STD_IN, exec_cmd1,
			ft_split(ft_strtok(NULL, ">"), ' ')[0], O_RDONLY);
	printf("redir1 is created\n");
//	exec_cmd2 = construct_exec_cmd(ft_split(ft_strtok(NULL, "|"), ' '));
//	printf("exec_cmd2 cmd name: %s\n", exec_cmd2->exec->argv[0]);
//	pipe_cmd1 = construct_pipe_cmd(redir_cmd1, exec_cmd2);
//	printf("pipe1 is created\n");
//	exec_cmd3 = construct_exec_cmd(ft_split(ft_strtok(NULL, ">"), ' '));
//	printf("exec_cmd3 cmd name: %s\n", exec_cmd3->exec->argv[0]);
//	pipe_cmd2 = construct_pipe_cmd(pipe_cmd1, exec_cmd3);
//	printf("pipe2 is created\n");
	redir_cmd2 = construct_redir_cmd(REDIR_STD_OUT, redir_cmd1,
			ft_split(ft_strtok(NULL, ">"), ' ')[0],
			O_WRONLY | O_CREAT | O_TRUNC);
	printf("redir2 is created\n");
	return (redir_cmd2);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		handle_cd(input);
		if (fork1() == 0)
			run_cmd(parse_cmd(input));
		free(input);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}
