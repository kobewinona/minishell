/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:06 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/21 03:59:26 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// @todo Why write this function if it exits in libft???
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

// @todo Where is "too many arguments" error???
void	exit_cmd(char **argv, t_msh **msh)
{
	int	exit_code;

	exit_code = 0;
	if (argv[1] != NULL && is_number(argv[1]))
	{
		exit_code = ft_atoi(argv[1]);
		printf("exit\nCode = %s\n", argv[1]);
		cleanup(msh);
		exit(exit_code);
	}
	else if (argv[1] != NULL && !is_number(argv[1]))
	{
		printf("exit\n");
		handle_err(msh, EXIT_INVALID_ARG, argv[1], 2);
	}
	cleanup(msh);
	rl_clear_history();
	printf("exit\n");
	exit(exit_code);
}
