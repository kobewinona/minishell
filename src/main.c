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


// //Testing linked lists for env
// int main(int argc, char **argv, char **envp)
// {
//     t_var_node *head;

//     head = copy_env_vars(envp);
    
    
//     printf("user = %s\n", get_env_var(head, argv[1]));
   
//     set_var_deleted(head, argv[1]);
    

//     printf("user after = %s\n", get_env_var(head, argv[1]));
    


//     return (0);

// }