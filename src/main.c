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
		handle_exec(&(cmd->exec));
	else if (cmd->type == T_PIPE)
		handle_pipe(&(cmd->pipe));
	else if (cmd->type == T_REDIR)
		handle_redir(&(cmd->redir));
	else if (cmd->type == T_HEREDOC)
		handle_heredoc(&(cmd->heredoc), UNSPECIFIED);
	else
		handle_err(ERROR, (t_err){T_SYS_ERR}, true);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*input_prompt;
	char	*input_tmp;

	(void)argc;
	(void)argv;
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
		run_cmd(parse_cmd(input_tmp, envp));
		wait(NULL);
		free(input);
	}
	clear_history();
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