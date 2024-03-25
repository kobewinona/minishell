/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linked_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:44:53 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/25 11:42:17 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_var_node(char *name, char *value)
{
	t_env	*new_element;

	new_element = (t_env *)malloc(sizeof(t_env));
	if (new_element == NULL)
		return (NULL);
	new_element->name = ft_strdup(name);
	if (value)
		new_element->value = ft_strdup(value);
	else
		new_element->value = NULL;
	new_element->is_value_assigned = value != NULL;
	new_element->is_deleted = false;
	new_element->next = NULL;
	return (new_element);
}

void	append_var_node(t_env **head, char *name, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_var_node(name, value);
	if (!name || !new_node)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

t_env	*copy_env_vars(t_msh **msh, char **envp)
{
	t_env	*head;
	char	**key_value_pair;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		key_value_pair = ft_split(envp[i], '=');
		if (!key_value_pair)
			return (handle_err(msh, SYSTEM, MALLOC, 1), NULL);
		append_var_node(&head, key_value_pair[0], key_value_pair[1]);
		free_double_array(key_value_pair);
		i++;
	}
	return (head);
}
