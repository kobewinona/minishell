/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:53:33 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/19 15:53:36 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(char **argv, t_msh **msh)

{
	t_var_node	*curr;

	curr =(*msh)->env_vars;
	while (curr)
	{
		if (!curr->deleted && curr->key_val_str && curr->value_assigned)
			printf("%s\n", curr->key_val_str);
		curr = curr->next;
	}

	(*msh)->exit_code = 0;

}