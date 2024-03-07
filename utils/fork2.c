/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:16:11 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/07 14:16:11 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// same as default fork, but with custom setup of handling signals
int	fork2(t_msh **msh)
{
	(*msh)->child_pid = fork();
	if ((*msh)->child_pid == ERROR)
		return (ERROR);
	if ((*msh)->child_pid == 0)
	{
		(*msh)->is_parent = false;
		if (ignore_signals(msh) == ERROR)
			exit(EXIT_FAILURE);
	}
	return ((*msh)->child_pid);
}
