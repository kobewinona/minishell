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

// void	handle_exit(t_msh **msh, int exit_code, bool is_safe)
// {
// 	if (is_safe)
// 	{
// 		if ((*msh)->curr_pid == 0)
// 		{
// 			cleanup(msh);
// 			exit(exit_code);
// 		}
// 		(*msh)->exit_code = exit_code;
// 	}
// 	else
// 	{
// 		cleanup(msh);
// 		exit(exit_code);
// 	}
// }

// void	run_cmd(t_msh **msh, t_cmd *cmd)
// {
// 	if (!cmd)
// 		return ;
// 	if (cmd->type == C_EXEC)
// 		handle_exec(msh, &(cmd->exec));
// 	else if (cmd->type == C_PIPE)
// 		handle_pipe(msh, &(cmd->pipe));
// 	else if (cmd->type == C_REDIR)
// 		handle_redir(msh, &(cmd->redir));
// 	g_state = IS_IDLE;
// }

// static void	run_minishell(t_msh **msh)
// {
// 	while (1)
// 	{
// 		(*msh)->org_stdin = dup(STDIN_FILENO);
// 		if ((*msh)->input)
// 			free((*msh)->input);
// 		put_prompt(msh);
// 		if (!(*msh)->input)
// 		{
// 			if (isatty(STDIN_FILENO))
// 				ft_putstr_fd("exit\n", STDOUT_FILENO);
// 			return ;
// 		}
// 		add_history((*msh)->input);
// 		if (parse_cmd(msh) == ERROR)
// 		{
// 			cleanup_cmds(&(*msh)->cmd);
// 			continue ;
// 		}
// 		prepare_fds(msh, &(*msh)->cmd);
// 		run_cmd(msh, (*msh)->cmd);
// 		cleanup_cmds(&(*msh)->cmd);
// 		close((*msh)->org_stdin);
// 	}
// }

// int	g_state;

// int	main(int argc, char **argv, char **envp)
// {
// 	t_msh	*msh;
// 	int		exit_code;

// 	(void)argc;
// 	(void)argv;
// 	g_state = IS_IDLE;
// 	msh = (t_msh *)malloc(sizeof(t_msh));
// 	if (!msh)
// 		return (EXIT_FAILURE);
// 	ft_memset(msh, 0, sizeof(t_msh));
// 	if (init_signals(&msh) == ERROR)
// 		return (free(msh), EXIT_FAILURE);
// 	msh->curr_pid = UNSPECIFIED;
// 	msh->env_vars = copy_env_vars(&msh, envp);
// 	increment_shlvl(&msh, msh->env_vars);
// 	run_minishell(&msh);
// 	exit_code = msh->exit_code;
// 	return (cleanup(&msh), exit_code);
// }

int err(char *str)
{
    while (*str)
        write(2, str++, 1);
    return 1;
}

int cd(char **argv, int i)
{
    if (i != 2)
        return err("error: cd: bad arguments\n");
    if (chdir(argv[1]) == -1)
        return err("error: cd: cannot change directory to "), err(argv[1]), err("\n");
    return 0;
}

int exec(char **argv, int i)
{
    int fd[2];
    int status;
    int has_pipe = argv[i] && !strcmp(argv[i], "|");

    if (!has_pipe && !strcmp(*argv, "cd"))
        return cd(argv, i);

    if (has_pipe && pipe(fd) == -1)
        return err("error: fatal\n");

    int pid = fork();
    if (!pid)
    {
        argv[i] = 0;
        if (has_pipe && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
            return err("error: fatal\n");
        if (!strcmp(*argv, "cd"))
            return cd(argv, i);
        execve(*argv, argv, __environ);
        return err("error: cannot execute "), err(*argv), err("\n");
    }

    waitpid(pid, &status, 0);
    if (has_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
        return err("error: fatal\n");
    return WIFEXITED(status) && WEXITSTATUS(status);
}

int main(int argc, char **argv)
{
    int    i = 0;
    int    status = 0;

    if (argc > 1)
    {
        while (argv[i] && argv[++i])
        {
            argv += i;
            i = 0;
            while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
                i++;
            if (i)
                status = exec(argv, i);
        }
    }
    return status;
}
