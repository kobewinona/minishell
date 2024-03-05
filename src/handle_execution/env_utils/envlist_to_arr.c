/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_to_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:08:52 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/17 17:08:53 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_list(t_var_node *env_vars)
{
	t_var_node	*curr_node;
	int			i;

	i = 0;
	curr_node = env_vars;
	while (curr_node)
	{
		if (!curr_node->deleted)
			i++;
		curr_node = curr_node->next;
	}
	return (i);
}

char	**envlist_to_arr(t_var_node *env_vars)
{
	int			len;
	t_var_node	*curr;
	char		**arr;
	int			i;

	i = 0;
	len = len_list(env_vars);
	curr = env_vars;
	arr = (char **) malloc(sizeof(char *) * len);
	if (arr == NULL)
		return (NULL);
	while (i < len - 1)
	{
		if (curr->value && !curr->deleted)
		{
			arr[i] = curr->key_val_str;
			i++;
		}
		curr = curr->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_envlist(t_var_node *env_vars)
{
	t_var_node *curr;
	t_var_node *next;

	curr = env_vars;
	while (curr)
	{
		next = curr->next;
		
		free(curr->name);
		free(curr->value);
		//free(curr->key_val_str);
		free(curr);

		curr = next;
	}
	
}