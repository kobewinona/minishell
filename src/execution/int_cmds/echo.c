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

int	echo(char **argv, t_var_node *env_vars)
{
	int	is_with_n_flag;
	int	i;

	i = 1;
	is_with_n_flag = false;
	replace_dollar_sign(argv, env_vars);	
	if (argv[i])
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
	return (SUCCESS);
}
