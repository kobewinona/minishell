/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:44:53 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/22 02:03:08 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retrieves a value of variable. Return NULL if not found
char	*get_env_var(t_env *head, char *varname)
{
	t_env	*curr;

	curr = head;
	while (curr)
	{
		if (!(ft_strncmp(varname, curr->name, 1000))
			&& curr->value_assigned && curr->value)
		{
			return (curr->value);
		}
		curr = curr->next;
	}
	return ("");
}

void	set_var_deleted(t_env *head, char *varname)
{
	t_env	*curr;
	t_env	*temp;
	t_env	*prev;

	prev = head;
	curr = head->next;
	while (curr)
	{
		if (!(ft_strncmp(varname, curr->name, 5000)))
		{
			temp = curr->next;
			curr = prev;
			free(curr->next->name);
			free(curr->next->value);
			free(curr->next);
			curr->next = temp;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

// updates value of env VAR or creates a new one
void	update_var(t_env *head, char *varname, char *value)
{
	char		*key_val_str;
	char		*substr;

	if (is_in_env(head, varname))
	{
		update_var_value(head, varname, value);
		return ;
	}
	substr = ft_strjoin(varname, "=");
	if (value)
	{
		key_val_str = ft_strjoin(substr, value);
		free(substr);
	}
	else
		key_val_str = substr;
	set_var_deleted(head, varname);
	append_var_node(&head, key_val_str);
	free(key_val_str);
}

void	increment_shlvl(t_env *env_vars)
{
	char	*new_shlvl;

	if (get_env_var(env_vars, "SHLVL"))
	{
		new_shlvl = ft_itoa(ft_atoi(get_env_var(env_vars, "SHLVL")) + 1);
		update_var(env_vars, "SHLVL", new_shlvl);
		free(new_shlvl);
	}
	else
		update_var(env_vars, "SHLVL", "1");
}
