/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:18:14 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/12 21:18:15 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tokstr(t_types tok)
{
	if (tok == T_REDIR_STDOUT)
		return (">");
	if (tok == T_REDIR_STDIN)
		return ("<");
	if (tok == T_APPEND_STDOUT)
		return (">>");
	if (tok == T_HEREDOC)
		return ("<<");
	if (tok == T_PIPE)
		return ("|");
	if (tok == T_DOUBLE_QUOTE)
		return ("\"");
	if (tok == T_SINGLE_QUOTE)
		return ("\'");
	return (NULL);
}
