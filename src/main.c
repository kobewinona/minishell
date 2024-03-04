/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:24:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/01 14:36:34 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cmd(t_msh **msh, t_cmd *cmd)
{
	int	res;

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
	t_cmd	*cmd;
	char	*input;
	char	*temp;

	while (1)
	{
		(*msh)->state = READ_STATE;
		input = readline(PRG_PROMPT);
		if (!input)
			break ;
		add_history(input);
		temp = input;
		cmd = parse_cmd(msh, temp);
		process_err(msh, false);
		if (cmd)
		{	(*msh)->state = EXEC_STATE;
			run_cmd(msh, cmd);
			cleanup_cmds(cmd);
		}
		free(input);
	}
}

// For signals
//if (WIFEXITED(g_pid))
// 		g_status = WEXITSTATUS(g_pid);
// 	if (WIFSIGNALED(g_pid))
// 	{
// 		g_status = WTERMSIG(g_pid);
// 		if (g_status != 131)
// 			g_status += 128;
// 	}

//HINT: a cool idea to build ft_linked_malloc()
// that allocates memory and keep it in a linked list to free easilly
int	main(int argc, char **argv, char **envp)
{
	t_msh		*msh;

	(void)argc;
	(void)argv;

	track_signals();
	msh = (t_msh *) malloc(sizeof(t_msh));
	if (!msh)
		return (EXIT_FAILURE);
	memset(msh, 0, sizeof(t_msh));
	msh->is_parent = true;
	msh->env_vars = copy_env_vars(envp);
	increment_shlvl(msh->env_vars);
	run_minishell(&msh);
	return (msh->exit_code);
}
