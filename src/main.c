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
	if (cmd->type == T_EXEC)
		handle_exec(cmd->exec);
	else if (cmd->type == T_PIPE)
		handle_pipe(cmd->pipe);
	else if (cmd->type == T_REDIR)
		handle_redir(cmd->redir);
	else if (cmd->type == T_HEREDOC)
		handle_heredoc(cmd->heredoc, UNSPECIFIED);
	else
		handle_err(ERROR, (t_err){T_SYS_ERR}, true);
}

int	main(void)
{
	char	*input;
	char	*input_prompt;
	char	*input_tmp;

	while (1)
	{
		input_prompt = ft_strjoin(PRG_NAME, INPUT_PROMPT);
		input = readline(input_prompt);
		free(input_prompt);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		handle_cd(input);
		input_tmp = input;
//		if (handle_err(fork(), (t_err){T_SYS_ERR, FORK}, false) == 0)
//			run_cmd(parse_cmd(input_tmp));
		run_cmd(parse_cmd(input_tmp)); // for debugging
		free(input);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}
