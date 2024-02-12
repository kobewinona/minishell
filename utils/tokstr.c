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

char	*tokstr(int token)
{
	if (token == REDIR_STDOUT_TOK)
		return ("`>'\n");
	if (token == REDIR_STDIN_TOK)
		return ("`<'\n");
	if (token == APPEND_STDOUT_TOK)
		return ("`>>'\n");
	if (token == HEREDOC_TOK)
		return ("`<<'\n");
	if (token == PIPE_TOK)
		return ("`|'\n");
	return (NULL);
}
