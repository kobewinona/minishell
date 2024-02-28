/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:45:46 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/16 21:45:46 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_msh **msh)
{
	char	*curr_dir;

	curr_dir = NULL;
	curr_dir = get_env_var((*msh)->env_vars, "PWD"); // replace with getting pwd from our list
//	if (!curr_dir)
//		handle_err(ERROR, (t_err){T_SYS_ERR, PWD}, true);
	ft_putstr_fd(curr_dir, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	//exit(EXIT_SUCCESS);
}
