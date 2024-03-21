/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:45:29 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 10:54:18 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	join_value(t_msh **msh, char *value)
{
	char	*temp;

	temp = ft_strjoin((*msh)->prompt, value);
	if (!temp)
		return (handle_err(msh, SYSTEM, MALLOC, 1), ERROR);
	free((*msh)->prompt);
	(*msh)->prompt = temp;
	return (SUCCESS);
}

int	update_prompt(t_msh **msh, char **argv, int i)
{
	char	*temp;

	if ((*msh)->prompt)
	{
		if (join_value(msh, argv[i]) == ERROR)
			return (ERROR);
	}
	else
	{
		(*msh)->prompt = ft_strdup(argv[i]);
		if (!(*msh)->prompt)
			return (handle_err(msh, SYSTEM, MALLOC, 1), ERROR);
	}
	if (argv[i + 1])
	{
		if (join_value(msh, " ") == ERROR)
			return (ERROR);
	}
	else
	{
		if (join_value(msh, PRG_PROMPT) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

void	put_prompt(t_msh **msh)
{
	if ((*msh)->prompt)
	{
		(*msh)->input = readline((*msh)->prompt);
		free((*msh)->prompt);
		(*msh)->prompt = NULL;
	}
	else
		(*msh)->input = readline(PRG_PROMPT);
}
