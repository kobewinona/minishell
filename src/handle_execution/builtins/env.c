/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:53:33 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/25 11:42:25 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(char **argv, t_msh **msh)
{
	t_env	*curr;

	(void)argv;
	curr = (*msh)->env_vars;
	while (curr)
	{
		if (curr->is_value_assigned && curr->value)
			printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
	handle_exit(msh, EXIT_SUCCESS, true);
}
