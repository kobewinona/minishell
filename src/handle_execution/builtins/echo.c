/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:22 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/20 01:37:32 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_flag(char *s)
{
	int	i;

	i = 0;
	if (!s || s[i++] != '-')
		return (false);
	while (s[i])
	{
		if (s[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	handle_exit(t_msh **msh, bool is_with_n_flag, int exit_code)
{
	if (!is_with_n_flag)
	{
		if (write(STDOUT_FILENO, "\n", 1) == ERROR)
			exit_code = EXIT_FAILURE;
	}
	if ((*msh)->curr_pid == 0)
	{
		cleanup(msh);
		exit(exit_code);
	}
	(*msh)->exit_code = EXIT_SUCCESS;
}

void	echo(char **argv, t_msh **msh)
{
	int	is_with_n_flag;
	int	i;

	i = 1;
	is_with_n_flag = false;
	while (argv[i])
	{
		if (is_valid_flag(argv[i]) && (i == 1 || (i > 1 && is_with_n_flag)))
		{
			is_with_n_flag = true;
			i++;
			continue ;
		}
		if (write(STDOUT_FILENO, argv[i], ft_strlen(argv[i])) == ERROR)
			handle_exit(msh, is_with_n_flag, EXIT_FAILURE);
		i++;
		if (argv[i])
		{
			if (write(STDOUT_FILENO, " ", 1) == ERROR)
				handle_exit(msh, is_with_n_flag, EXIT_FAILURE);
		}
	}
	handle_exit(msh, is_with_n_flag, EXIT_SUCCESS);
}
