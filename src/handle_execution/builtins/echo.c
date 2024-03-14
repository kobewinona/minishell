/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:22 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/12 11:05:23 by dklimkin         ###   ########.fr       */
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
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!is_with_n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	(*msh)->exit_code = 0;
}
