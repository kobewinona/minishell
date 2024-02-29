/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:50:25 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/16 12:50:27 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char **argv, t_msh **msh)
{
	int	i;

	i = 1;
	while (argv[i])
	{

		set_var_deleted((*msh)->env_vars, argv[i]);
		i++;
	}
	(*msh)->exit_code = 0;
}