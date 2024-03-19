/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:18:14 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/20 03:11:53 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_encaps_tokens(t_types tok)
{
	if (tok == T_CURLY_OPEN)
		return ("{");
	if (tok == T_CURLY_CLOSE)
		return ("}");
	if (tok == T_SQUARE_OPEN)
		return ("[");
	if (tok == T_SQUARE_CLOSE)
		return ("]");
	if (tok == T_BRACKET_OPEN)
		return ("(");
	if (tok == T_BRACKET_CLOSE)
		return (")");
	return (NULL);
}

char	*tokstr(t_types tok)
{
	char	*res;

	res = NULL;
	if (tok == T_REDIR_STDOUT)
		res = ">";
	else if (tok == T_REDIR_STDIN)
		res = "<";
	else if (tok == T_APPEND_STDOUT)
		res = ">>";
	else if (tok == T_HEREDOC)
		res = "<<";
	else if (tok == T_PIPE)
		res = "|";
	else if (tok == T_DOUBLE_QUOTE)
		res = "\"";
	else if (tok == T_SINGLE_QUOTE)
		res = "\'";
	else
		res = handle_encaps_tokens(tok);
	return (res);
}
