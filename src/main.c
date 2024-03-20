/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:24:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/20 05:37:50 by dklimkin         ###   ########.fr       */
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

int	run_cmd(t_msh **msh, t_cmd *cmd)
{
	int	res;

	if (!cmd)
		return (0);
	if (cmd->type == T_EXEC)
		res = handle_exec(msh, &(cmd->exec));
	else if (cmd->type == T_PIPE)
		res = handle_pipe(msh, &(cmd->pipe));
	else if (cmd->type == T_REDIR)
		res = handle_redir(msh, &(cmd->redir));
	if (!(*msh)->is_parent)
		exit((*msh)->exit_code);
	return (res);
}

static void	run_minishell(t_msh **msh)
{
	while (1)
	{
		(*msh)->org_fd = dup(STDIN_FILENO);
		(*msh)->input = readline(PRG_PROMPT);
		if (!(*msh)->input)
		{
			printf("exit\n");
			break ;
		}
		add_history((*msh)->input);
		if (parse_cmd(msh) == ERROR)
		{
			free((*msh)->input);
			continue ;
		}
		if (prepare_fds(msh, &(*msh)->cmd) == ERROR)
			cleanup_cmds(&(*msh)->cmd);
		(*msh)->exit_code = run_cmd(msh, (*msh)->cmd);
		cleanup_cmds(&(*msh)->cmd);
		free((*msh)->input);
		close((*msh)->org_fd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_msh		*msh;

	(void)argc;
	(void)argv;
	printf("parent pid %d\n", getpid());
	msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		return (EXIT_FAILURE);
	memset(msh, 0, sizeof(t_msh));
	if (init_signals_handle(&msh) == ERROR)
		return (free(msh), EXIT_FAILURE);
	msh->curr_pid = UNSPECIFIED;
	msh->is_parent = true;
	msh->env_vars = copy_env_vars(envp);
	msh->script_name = get_env_var(msh->env_vars, "PWD");
	increment_shlvl(msh->env_vars);
	run_minishell(&msh);
	return (msh->exit_code);
}
