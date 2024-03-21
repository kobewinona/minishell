/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:45:46 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 11:21:24 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_msh **msh)

{
	char	*curr_dir;

	curr_dir = NULL;
	curr_dir = get_env_var((*msh)->env_vars, "PWD");
	if (curr_dir)
		ft_putstr_fd(curr_dir, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	handle_exit(msh, EXIT_SUCCESS, true);
}
