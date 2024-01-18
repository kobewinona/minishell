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
	if (cmd->type == EXEC_CMD)
		handle_exec(cmd->exec);
	else if (cmd->type == PIPE_CMD)
		handle_pipe(cmd->pipe);
	else if (cmd->type == REDIR_CMD)
		handle_redir(cmd->redir);
	else if (cmd->type == HEREDOC)
		handle_heredoc(cmd->heredoc, -1);
	else
		handle_err(ERROR, NULL, NULL, true);
}

static t_cmd	*parse_cmd(char *input)
{
	t_cmd	*exec_cmd1 = NULL, *exec_cmd2 = NULL, *exec_cmd3 = NULL, *pipe_cmd1 = NULL, *pipe_cmd2 = NULL, *redir_cmd1 = NULL, *redir_cmd2 = NULL, *redir_cmd3 = NULL, *append_cmd1 = NULL, *heredoc_cmd1 = NULL;

	exec_cmd1 = construct_exec_cmd(ft_split(ft_strtok(input, "<"), ' '));
	heredoc_cmd1 = construct_heredoc_cmd(exec_cmd1, "eof");
	redir_cmd1 = construct_redir_cmd(REDIR_STDOUT, heredoc_cmd1, "sorted.txt",  O_WRONLY | O_CREAT | O_TRUNC);
	return (redir_cmd1);
}

int	main(void)
{
	char	*input;
	char	*input_prompt;

	while (1)
	{
		input_prompt = ft_strjoin(NAME, PROMPT);
		input = readline(input_prompt);
		free(input_prompt);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		handle_cd(input);
		if (handle_err(fork(), FORK, NULL, false) == 0)
			run_cmd(parse_cmd(input));
		free(input);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}
