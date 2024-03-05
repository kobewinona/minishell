/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linked_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:44:53 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/14 16:45:06 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retrieves a value of variable. Return NULL if not found
char	*get_env_var(t_var_node *head, char *varname)
{
	t_var_node	*curr;

	curr = head;
	while (curr)
	{
		if (!((ft_strncmp(varname, curr->name, 5000)) | !curr->value_assigned))
		{
			return (curr->value);
		}
		curr = curr->next;
	}
	return (NULL);
}

void	set_var_deleted(t_var_node *head, char *varname)
{
	t_var_node	*curr;
	t_var_node	*temp;
	t_var_node	*prev;

	prev = NULL;
	curr = head;
	while (curr)
	{
		if (!(ft_strncmp(varname, curr->name, 5000)))
		{
		
			temp = curr->next;
			curr = prev;
			free(curr->next);
			curr->next = temp;
		}
		prev = curr;
		curr = curr->next;
	}
}

// updates value of env VAR or creates a new one
void	update_var(t_var_node *head, char *varname, char *value)
{
	t_var_node	*curr;
	char		*key_val_str;

	key_val_str = ft_strjoin(varname, "=");
	if (value)
		key_val_str = ft_strjoin(key_val_str, value);
	curr = head;
	while (curr)
	{
		if (!(ft_strncmp(varname, curr->name, 5000)))
		{
			curr->deleted = false;
			if (value)
			{
				curr->value = ft_strdup(value);
				curr->value_assigned = true;
			}
			else
			{
				curr->value = NULL;
				curr->value_assigned = is_char_there(key_val_str, '=');
			}
			curr->key_val_str = key_val_str;
			return ;
		}
		curr = curr->next;
	}
	append_var_node(&head, key_val_str);
}

void	increment_shlvl(t_var_node *env_vars)
{
	int	new_shlvl;

	if (get_env_var(env_vars, "SHLVL"))
	{
		new_shlvl = ft_atoi(get_env_var(env_vars, "SHLVL")) + 1;
		update_var(env_vars, "SHLVL", ft_itoa(new_shlvl));
	}
	else
		update_var(env_vars, "SHLVL", "1");
}
