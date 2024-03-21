/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:37:43 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/22 01:44:33 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_var_value(t_env *head, char *varname, char *new_val)
{
	t_env	*curr;

	curr = head;
	while (curr)
	{
		if (!(ft_strncmp(varname, curr->name, 5000)))
		{
			if (curr->value)
				free(curr->value);
			if (new_val)
				curr->value = ft_strdup(new_val);
			else
				curr->value = ft_strdup("");
			return ;
		}
		curr = curr->next;
	}
	return ;
}

bool	is_in_env(t_env *head, char *varname)
{
	t_env	*curr;

	curr = head;
	while (curr)
	{
		if (!(ft_strncmp(varname, curr->name, 5000)))
			return (true);
		curr = curr->next;
	}
	return (false);
}
