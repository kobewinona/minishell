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
	int			i;
	t_var_node *curr_node;

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


static char	*get_keyval(t_var_node *node)
{
	char	*keyvalstr;
	
	if (node->value)
	{
		keyvalstr = ft_strjoin(node->name, "=");
		keyvalstr = ft_strjoin(keyvalstr, node->value);
		return (keyvalstr);
	}
	return (NULL);
}

char	**envlist_to_arr(t_var_node *env_vars)
{
	int	len;
	t_var_node *curr;
	char	**arr;
	int		i;

	i = 0;
	len = len_list(env_vars);
	curr = env_vars;
	arr = (char **) malloc(sizeof(char *) * (len + 1));
	if (arr == NULL)
		return (NULL);
	while (i < len)
	{
		if (curr->value && !curr->deleted)
		{
			arr[i] = get_keyval(curr);
			i++;
		}
		curr = curr->next;
	}
	arr[i] = NULL;
	return (arr);
}