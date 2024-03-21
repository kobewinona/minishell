/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:22 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 01:49:05 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_n_opt(char *s)
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

static void	handle_newline(t_msh **msh, bool is_with_newline)
{
	if (is_with_newline)
	{
		if (write(STDOUT_FILENO, "\n", 1) == ERROR)
			handle_exit(msh, EXIT_FAILURE);
	}
}

// @todo update exit handling
void	echo(char **argv, t_msh **msh)
{
	bool	is_with_newline;
	int		i;

	i = 1;
	is_with_newline = true;
	while (argv[i])
	{
		if (is_valid_n_opt(argv[i]) && (i == 1 || (i > 1 && is_with_newline)))
		{
			is_with_newline = false;
			i++;
			continue ;
		}
		if (write(STDOUT_FILENO, argv[i], ft_strlen(argv[i])) == ERROR)
			handle_exit(msh, EXIT_FAILURE);
		i++;
		if (argv[i])
		{
			if (write(STDOUT_FILENO, " ", 1) == ERROR)
				handle_exit(msh, EXIT_FAILURE);
		}
	}
	handle_newline(msh, is_with_newline);
	handle_exit(msh, EXIT_SUCCESS);
}
