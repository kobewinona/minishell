/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:37:43 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/13 13:37:58 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_var_value(t_var_node *head, char *varname, char *new_val)
{
	t_var_node *curr;

	curr = head;
	while (curr)
	{
		if (!(ft_strncmp(varname, curr->name, 5000)))
		{
			if (curr->value)
				free(curr->value);
			curr->value = ft_strdup(new_val);
			return ;
		}
		curr = curr->next;
	}
	return ;
}

bool	is_in_env(t_var_node *head, char *varname)
{
	t_var_node *curr;

	curr = head;
	while (curr)
	{
		if (!(ft_strncmp(varname, curr->name, 5000)))
			return (true);
		
		curr = curr->next;
	}
	return (false);
}
