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

// need to return exit code passed as arg / ext code of last executed cmdq

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
	//!!!!
	//Need to free evrth before exiting
	if (argv[1] != NULL && is_number(argv[1]))
	{
		printf("exit\n");
		exit(ft_atoi(argv[1]));
	}
	else if (argv[1] != NULL && !is_number(argv[1]))
	{
		printf("exit\n");
		print_err(msh, (t_err){T_OTHER_ERR, EXIT, EXIT_INVALID_ARG_MSG1}, true);
	}
	exit(SUCCESS);
}