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
	char	*input;
	char	*temp;

	while (1)
	{
		(*msh)->cmd = NULL;
		input = readline(PRG_PROMPT);
		if (!input)
			break ;
		if (!is_emptystr(input))
		{
			add_history(input);
			temp = input;
			(*msh)->cmd = parse_cmd(msh, temp);
			prepare_fds(msh, &(*msh)->cmd);
		}
		if ((*msh)->cmd)
		{
			(*msh)->exit_code = run_cmd(msh, (*msh)->cmd);
			cleanup_cmds(&(*msh)->cmd);
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_msh		*msh;

	(void)argc;
	(void)argv;

	printf("Minishell starts...\n");
	msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		return (EXIT_FAILURE);
	memset(msh, 0, sizeof(t_msh));
	if (track_signals(&msh) == ERROR)
		return (free(msh), EXIT_FAILURE);
	msh->child_pid = UNSPECIFIED;
	msh->is_parent = true;
	msh->env_vars = copy_env_vars(envp);
	msh->script_name = get_env_var(msh->env_vars, "PWD");
	increment_shlvl(msh->env_vars);
	run_minishell(&msh);
	return (msh->exit_code);
}


//Test for leaks

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;

// 	t_var_node *head;

// 	head = copy_env_vars(envp);

// 	increment_shlvl(head);
// 	increment_shlvl(head);
// 	increment_shlvl(head);
// 	increment_shlvl(head);

// 	set_var_deleted(head, "USER");
// 	set_var_deleted(head, "HOME");

// 	update_var(head, "VAR3", "KOLSFS");
// 	set_var_deleted(head, "PATH");

// 	set_var_deleted(head, "VAR3");
// 	update_var(head, "MYVAR", "HUETA");
// 	update_var(head, "MYVAR", "HUETA_DODO");
	


// 	free_envlist(head);
// 	return (0);
// }
