/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:06 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/14 14:03:07 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_number(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

void	exit_cmd(char **argv, t_msh **msh)
{
	free_envlist((*msh)->env_vars);
	cleanup_cmds(&(*msh)->cmd);
	if (argv[1] != NULL && is_number(argv[1]))
	{
		free((*msh));
		printf("exit\n");
		exit(ft_atoi(argv[1]));
	}
	else if (argv[1] != NULL && !is_number(argv[1]))
	{
		printf("exit\n");
		handle_err(msh, (t_err){
			T_OTHER_ERR, EXIT, EXIT_INVALID_ARG_MSG1}, true);
	}
	free((*msh));
	exit(SUCCESS);
}
