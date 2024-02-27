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

int	unset(char **argv, t_var_node *env_vars)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		set_var_deleted(env_vars, argv[i]);
		i++;
	}
	return (SUCCESS);
}