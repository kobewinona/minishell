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
		cmd = NULL;
		input = readline(PRG_PROMPT);
		if (!input)
			break ;
		if (!is_emptystr(input))
		{
			add_history(input);
			temp = input;
			cmd = parse_cmd(msh, temp);
			prepare_fds(msh, &cmd);
		}
		if (cmd)
		{	
			run_cmd(msh, cmd);
			cleanup_cmds(&cmd);
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


//GLobal var for 
bool is_parent = true;

// int	main(int argc, char **argv, char **envp)
// {
// 	t_msh		*msh;

// 	(void)argc;
// 	(void)argv;
// 	track_signals(false);
// 	msh = (t_msh *)malloc(sizeof(t_msh));
// 	if (!msh)
// 		return (EXIT_FAILURE);
// 	memset(msh, 0, sizeof(t_msh));
// 	msh->chld_pid = UNSPECIFIED;
// 	msh->is_parent = true;
// 	msh->env_vars = copy_env_vars(envp);
// 	msh->script_name = get_env_var(msh->env_vars, "PWD");
// 	increment_shlvl(msh->env_vars);
// 	run_minishell(&msh);
// 	return (msh->exit_code);
// }



//Checking leaks in env utils
// Note:
// better to set_var_deleted everytime we update it
// to avoid leaks
int	main(int argc, char **argv, char **envp)
{
	t_var_node *env_vars;
	t_var_node *env_vars2;

	env_vars = copy_env_vars(envp);
	env_vars2 = copy_env_vars(envp);
	printf("path, %s\n", get_env_var(env_vars, "PATH"));
	update_var(env_vars, "VAR", "WORLDDDDDDDD");
	set_var_deleted(env_vars, "VAR");
	update_var(env_vars, "VAR", "WOFDFDFD");
	// increment_shlvl(env_vars);
	//increment_shlvl(env_vars2);
	free_envlist(env_vars);
	free_envlist(env_vars2);
	

	return (0);
}