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
//	else if (cmd->type == T_HEREDOC)
//		handle_heredoc(&(cmd->heredoc), UNSPECIFIED);
	else
		handle_err(ERROR, (t_err){T_SYS_ERR}, true);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		*input_prompt;
	char		*input_tmp;
	t_cmd		*cmd;
	t_var_node	*env_vars;

	printf("....Starting minishell...\n");
	env_vars = copy_env_vars(envp);

	//update shlvl
	int new_shlvl;

	new_shlvl = ft_atoi(get_env_var(env_vars, "SHLVL")) + 1;
	update_var(env_vars, "SHLVL", ft_itoa(new_shlvl));

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
		handle_cd(input, env_vars);
		input_tmp = input;
		cmd = parse_cmd(input_tmp, env_vars);
		run_cmd(cmd);
		wait(NULL);
		free(input);
	}
	clear_history();
	return (EXIT_SUCCESS);
}
