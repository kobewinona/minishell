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

	printf("get_env_var\n");
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

	prev = head;
	curr = head->next;
	printf("set_vard_deleted()\n");
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
			//return ;
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
	char		*substr;

	printf("update_var()\n");
	substr = ft_strjoin(varname, "=");
	if (value)
	{
		key_val_str = ft_strjoin(substr, value);
		free(substr);
	}
	else
		key_val_str = substr;
	curr = head;
	set_var_deleted(head, varname);
	append_var_node(&head, key_val_str);
	free(key_val_str);
}

void	increment_shlvl(t_var_node *env_vars)
{
	char	*new_shlvl;

	printf("shlvl  before = %s\n", get_env_var(env_vars, "SHLVL"));
	if (get_env_var(env_vars, "SHLVL"))
	{

		
		new_shlvl = ft_itoa(ft_atoi(get_env_var(env_vars, "SHLVL")) + 1);
		update_var(env_vars, "SHLVL", new_shlvl);
		free(new_shlvl);
		
	}
	else
		update_var(env_vars, "SHLVL", "1");
	printf("shlvl  after = %s\n", get_env_var(env_vars, "SHLVL"));
}
