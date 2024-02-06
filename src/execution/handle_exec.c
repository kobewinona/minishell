/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:11:26 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/16 16:11:27 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*construct_exec_cmd(char **argv)
{
	t_cmd	*cmd;

	if (argv[0] == NULL)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		handle_err(ERROR, argv[0], MALLOC, true);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->exec = (t_exec *)malloc(sizeof(t_exec));
	if (!cmd->exec)
	{
		free(cmd);
		handle_err(ERROR, argv[0], MALLOC, true);
	}
	ft_memset(cmd->exec, 0, sizeof(t_cmd));
	cmd->type = EXEC_CMD;
	cmd->exec->argv = argv;
	return (cmd);
}

void	handle_exec(t_exec *params)
{
	if (ft_strncmp(params->argv[0], CD, ft_strlen(CD)))
	{
		if (!ft_strncmp(params->argv[0], ECHO, ft_strlen(ECHO)))
			echo(params->argv);
		else if (!ft_strncmp(params->argv[0], PWD, ft_strlen(PWD)))
			pwd();
		else
			handle_ext_cmd(params->argv);
	}
}
