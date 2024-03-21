/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:06 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/21 11:28:42 by dklimkin         ###   ########.fr       */
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
	int	exit_code;

	exit_code = 0;
	if (argv[1])
	{
		if (!is_number(argv[1]))
		{
			printf("exit\n");
			return (handle_err(msh, EXIT_INVALID_ARG, argv[1], 2));
		}
		if (argv[2] != NULL)
		{
			printf("exit\n");
			return (handle_err(msh, TOO_MANY_ARGS, EXIT, 1));
		}
		exit_code = ft_atoi(argv[1]);
	}
	printf("exit\n");
	handle_exit(msh, exit_code, false);
}
