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

int	pwd(t_var_node *env_vars)
{
	char	*curr_dir;

	curr_dir = NULL;
	curr_dir = get_env_var(env_vars, "PWD"); // replace with getting pwd from our list
//	if (!curr_dir)
//		handle_err(ERROR, (t_err){T_SYS_ERR, PWD}, true);
	ft_putstr_fd(curr_dir, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
