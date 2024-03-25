/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_to_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:08:52 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/25 11:41:03 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_list(t_env *env_vars)
{
	t_env	*curr_node;
	int		i;

	i = 0;
	curr_node = env_vars;
	while (curr_node)
	{
		if (curr_node->is_value_assigned && curr_node->value)
			i++;
		curr_node = curr_node->next;
	}
	return (i + 1);
}

char	**envlist_to_arr(t_env *env_vars)
{
	int		len;
	t_env	*curr;
	char	**arr;
	int		i;
	char	*substr;

	i = 0;
	len = len_list(env_vars);
	curr = env_vars;
	arr = (char **) malloc(sizeof(char *) * (len + 1));
	if (arr == NULL)
		return (NULL);
	while (i < len - 1)
	{
		if (curr->is_value_assigned && curr->value)
		{
			substr = ft_strjoin(curr->name, "=");
			arr[i] = ft_strjoin(substr, curr->value);
			free(substr);
			i++;
		}
		curr = curr->next;
	}
	arr[i] = NULL;
	return (arr);
}
