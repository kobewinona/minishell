/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 01:31:36 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/22 04:15:56 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_array(char **array)
{
	char	**temp;

	temp = array;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(array);
}

bool	is_emptystr(const char *s)
{
	if (!s)
		return (false);
	while ((*s))
	{
		if (!ft_isspace((*s)))
			return (false);
		s++;
	}
	return (true);
}

void	update_exit_code(t_msh **msh, int exit_code)
{
	if (WIFSIGNALED(exit_code))
		(*msh)->exit_code = 128 + WTERMSIG(exit_code);
	if (WIFEXITED(exit_code))
		(*msh)->exit_code = WEXITSTATUS(exit_code);
}

char	*char_to_str(char *s)
{
	if ((*s) && (*(s + 1)))
		(*(s + 1)) = '\0';
	return (s);
}

char	*tokstr(t_tok tok)
{
	if (tok == T_R_STDOUT)
		return (">");
	if (tok == T_R_STDIN)
		return ("<");
	if (tok == T_R_APPEND)
		return (">>");
	if (tok == T_R_HEREDOC)
		return ("<<");
	if (tok == T_PIPE)
		return ("|");
	if (tok == T_DOUBLE_QUOTE)
		return ("\"");
	if (tok == T_SINGLE_QUOTE)
		return ("\'");
	return (NULL);
}
