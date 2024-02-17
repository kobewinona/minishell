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

void	run_cmd(t_cmd *cmd, t_var_node *env_vars)
{
	if (cmd->type == T_EXEC)
		handle_exec(&(cmd->exec), env_vars);
	else if (cmd->type == T_PIPE)
		handle_pipe(&(cmd->pipe), env_vars);
	else if (cmd->type == T_REDIR)
		handle_redir(&(cmd->redir), env_vars);
	else if (cmd->type == T_HEREDOC)
		handle_heredoc(&(cmd->heredoc), UNSPECIFIED, env_vars);
	else
		handle_err(ERROR, (t_err){T_SYS_ERR}, true);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		*input_prompt;
	char		*input_tmp;
	t_var_node	*env_vars;

	env_vars = copy_env_vars(envp);
	while (1)
	{
		input_prompt = ft_strjoin(PRG_NAME, INPUT_PROMPT);
		input = readline(input_prompt);
		free(input_prompt);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		handle_cd(input, env_vars);
		input_tmp = input;
		run_cmd(parse_cmd(input_tmp, envp), env_vars);
		wait(NULL);
		free(input);
	}
	clear_history();
	return (EXIT_SUCCESS);
}


//  int main(int argc, char **argv, char **envp)
// {
//     t_var_node *head;
// 	char *fake_envp[] = {"MYVAR=HelloWorld", "NAME=STAS", NULL};

//     head = copy_env_vars(envp);

// 	char **mycopy = envlist_to_arr(head);

// 	int i = 0;

// 	printf("%s\n", mycopy[0]);
	
	
//     return (0);

// }