/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:24:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 08:00:42 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup(t_msh **msh)
{
	free_envlist((*msh)->env_vars);
	cleanup_cmds(&(*msh)->cmd);
	free((*msh)->input);
	free((*msh));
	rl_clear_history();
}

void	handle_exit(t_msh **msh, int exit_code)
{
	if ((*msh)->curr_pid == 0)
	{
		cleanup(msh);
		exit(exit_code);
	}
	(*msh)->exit_code = exit_code;
}

void	run_cmd(t_msh **msh, t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == T_EXEC)
		handle_exec(msh, &(cmd->exec));
	else if (cmd->type == T_PIPE)
		handle_pipe(msh, &(cmd->pipe));
	else if (cmd->type == T_REDIR)
		handle_redir(msh, &(cmd->redir));
}

static void	run_minishell(t_msh **msh)
{
	while (1)
	{
		(*msh)->org_fd = dup(STDIN_FILENO);
		if ((*msh)->input)
			free((*msh)->input);
		(*msh)->input = readline(PRG_PROMPT);
		if (!(*msh)->input)
		{
			printf("exit\n");
			break ;
		}
		add_history((*msh)->input);
		if (parse_cmd(msh) == ERROR || !(*msh)->cmd)
			continue ;
		if (prepare_fds(msh, &(*msh)->cmd) == ERROR)
		{
			cleanup_cmds(&(*msh)->cmd);
			continue ;
		}
		run_cmd(msh, (*msh)->cmd);
		cleanup_cmds(&(*msh)->cmd);
		close((*msh)->org_fd);
	}
}

int	g_state;

int	main(int argc, char **argv, char **envp)
{
	t_msh		*msh;

	(void)argc;
	(void)argv;
	g_state = IS_IDLE;
	msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		return (EXIT_FAILURE);
	ft_memset(msh, 0, sizeof(t_msh));
	if (init_signals(&msh) == ERROR)
		return (free(msh), EXIT_FAILURE);
	msh->curr_pid = UNSPECIFIED;
	msh->env_vars = copy_env_vars(envp);
	msh->script_name = get_env_var(msh->env_vars, "PWD");
	increment_shlvl(msh->env_vars);
	run_minishell(&msh);
	return (msh->exit_code);
}
