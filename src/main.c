/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:24:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/25 10:30:42 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exit(t_msh **msh, int exit_code, bool is_safe)
{
	if (is_safe)
	{
		if ((*msh)->curr_pid == 0)
		{
			cleanup(msh);
			exit(exit_code);
		}
		(*msh)->exit_code = exit_code;
	}
	else
	{
		cleanup(msh);
		exit(exit_code);
	}
}

void	run_cmd(t_msh **msh, t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == C_EXEC)
		handle_exec(msh, &(cmd->exec));
	else if (cmd->type == C_PIPE)
		handle_pipe(msh, &(cmd->pipe));
	else if (cmd->type == C_REDIR)
		handle_redir(msh, &(cmd->redir));
	g_state = IS_IDLE;
}

static void	run_minishell(t_msh **msh)
{
	while (1)
	{
		(*msh)->org_stdin = dup(STDIN_FILENO);
		if ((*msh)->input)
			free((*msh)->input);
		put_prompt(msh);
		if (!(*msh)->input)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", STDOUT_FILENO);
			return ;
		}
		add_history((*msh)->input);
		if (parse_cmd(msh) == ERROR)
		{
			cleanup_cmds(&(*msh)->cmd);
			continue ;
		}
		prepare_fds(msh, &(*msh)->cmd);
		run_cmd(msh, (*msh)->cmd);
		cleanup_cmds(&(*msh)->cmd);
		close((*msh)->org_stdin);
	}
}

int	g_state;

int	main(int argc, char **argv, char **envp)
{
	t_msh	*msh;
	int		exit_code;

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
	msh->env_vars = copy_env_vars(&msh, envp);
	increment_shlvl(&msh, msh->env_vars);
	run_minishell(&msh);
	exit_code = msh->exit_code;
	return (cleanup(&msh), exit_code);
}
