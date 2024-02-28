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

//Dima's version

void	echo(char **argv,  t_msh **msh)
{
	int	is_with_n_flag;
	int	i;

	i = 1;
	replace_dollar_sign(argv, (*msh)->env_vars, msh);
	is_with_n_flag = !ft_strncmp(argv[i], "-n", 2);
	if (is_with_n_flag == true)
		i = 2;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (is_with_n_flag == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
