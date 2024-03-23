/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:24:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/23 07:47:21 by dklimkin         ###   ########.fr       */
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
}

static void	handling_org_fds(t_msh **msh, bool is_start)
{
	if (is_start)
	{
		(*msh)->org_fds[0] = dup(STDIN_FILENO);
		(*msh)->org_fds[1] = dup(STDOUT_FILENO);
		(*msh)->org_fds[2] = dup(STDERR_FILENO);
		return ;
	}
	close((*msh)->org_fds[0]);
	close((*msh)->org_fds[1]);
	close((*msh)->org_fds[2]);
}

static void	run_minishell(t_msh **msh)
{
	while (1)
	{
		handling_org_fds(msh, true);
		if ((*msh)->input)
			free((*msh)->input);
		put_prompt(msh);
		if (!(*msh)->input)
		{
			printf("exit\n");
			return (cleanup(msh));
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
		handling_org_fds(msh, false);
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
	msh->env_vars = copy_env_vars(envp);
	increment_shlvl(msh->env_vars);
	run_minishell(&msh);
	exit_code = msh->exit_code;
	return (cleanup(&msh), exit_code);
	return (0);
}
