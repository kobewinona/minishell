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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*input_prompt;
	char	*input_tmp;

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
		input_tmp = input;
		// if (handle_err(fork(), FORK, NULL, false) == 0)
		// 	run_cmd(parse_cmd(input_tmp));
		run_cmd(parse_cmd(input_tmp)); //FOR DEBUG
		free(input);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}


 //Testing linked lists for env
//  int main(int argc, char **argv, char **envp)
// {
//     t_var_node *head;

//     head = copy_env_vars(envp);

//     printf("user = %s\n", get_env_var(head, "SHLVL"));
   
//    	set_var_deleted(head, "SHLVL");
//     update_var(head, "SHLVL", "350");
//     printf("user = %s\n", get_env_var(head, "SHLVL"));

// 	update_var(head, "HOME", "TAMBOV");
// 	printf("user = %s\n", get_env_var(head, "HOME"));

// 	update_var(head, "HELLO", "STAS");
// 	printf("user = %s\n", get_env_var(head, "HELLO"));
// 	set_var_deleted(head, "HELLO");
// 	printf("user = %s\n", get_env_var(head, "HELLO"));

//     return (0);

// }