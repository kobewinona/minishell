/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:50:25 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/21 11:21:28 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char **argv, t_msh **msh)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		set_var_deleted(msh, (*msh)->env_vars, argv[i]);
		i++;
	}
	handle_exit(msh, (*msh)->exit_code, true);
}
