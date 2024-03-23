/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linked_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:44:53 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/23 15:54:06 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_var_node(char *key_val_str)
{
	t_env	*new_element;
	char	**split_arr;

	new_element = (t_env *)malloc(sizeof(t_env));
	if (new_element == NULL)
		return (NULL);
	split_arr = ft_split(key_val_str, '=');
	new_element->name = ft_strdup(split_arr[0]);
	if (split_arr[1])
	{
		new_element->value = ft_strdup(split_arr[1]);
		new_element->value_assigned = true;
	}
	else
	{
		new_element->value = NULL;
		new_element->value_assigned = false;
	}
	new_element->key_val_str = key_val_str;
	new_element->is_numeric = false;
	new_element->deleted = false;
	new_element->next = NULL;
	free_double_array(split_arr);
	return (new_element);
}

void	append_var_node(t_env **head, char *key_val_str)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_var_node(key_val_str);
	if (key_val_str == NULL || new_node == NULL)
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

t_env	*copy_env_vars(char **envp)
{
	t_env	*head;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		append_var_node(&head, envp[i]);
		i++;
	}
	return (head);
}
