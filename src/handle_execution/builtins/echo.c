/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:22 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 11:01:15 by dklimkin         ###   ########.fr       */
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

static void	handle_print(t_msh **msh, char **argv, int i, bool is_with_newline)
{
	if (is_with_newline)
	{
		if (write(STDOUT_FILENO, argv[i], ft_strlen(argv[i])) == ERROR)
			handle_exit(msh, EXIT_FAILURE);
		if (argv[i + 1])
		{
			if (write(STDOUT_FILENO, " ", 1) == ERROR)
				handle_exit(msh, EXIT_FAILURE);
		}
	}
	else
	{
		if (update_prompt(msh, argv, i) == ERROR)
			handle_exit(msh, EXIT_FAILURE);
	}
}

// @todo update exit handling
void	echo(char **argv, t_msh **msh)
{
	char	*temp;
	bool	is_with_newline;
	int		i;

	i = 1;
	is_with_newline = true;
	while (argv[i])
	{
		if (is_valid_n_opt(argv[i]) && (i == 1 || (i > 1 && !is_with_newline)))
		{
			is_with_newline = false;
			i++;
			continue ;
		}
		handle_print(msh, argv, i, is_with_newline);
		i++;
	}
	if (is_with_newline)
	{
		if (write(STDOUT_FILENO, "\n", 1) == ERROR)
			handle_exit(msh, EXIT_FAILURE);
	}
	handle_exit(msh, EXIT_SUCCESS);
}
