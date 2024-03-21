/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_strtok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:53:08 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/22 04:17:55 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_curr_tok_type(char **tok, t_tok *curr_tok)
{
	if ((**tok) == '>')
	{
		if (*(*tok + 1) == '>')
		{
			(*curr_tok) = T_R_APPEND;
			(**tok) = ' ';
			(*tok)++;
			return ;
		}
		(*curr_tok) = T_R_STDOUT;
		return ;
	}
	if ((**tok) == '<')
	{
		if (*(*tok + 1) == '<')
		{
			(*curr_tok) = T_R_HEREDOC;
			(**tok) = ' ';
			(*tok)++;
			return ;
		}
		(*curr_tok) = T_R_STDIN;
		return ;
	}
	(*curr_tok) = T_NO_TOK;
}

static void	update_end(char *start, char **end, const char *sep, t_tok *tok)
{
	bool	is_in_single_quotes;
	bool	is_in_double_quotes;

	*end = start;
	is_in_single_quotes = false;
	is_in_double_quotes = false;
	while (**end)
	{
		if (**end == T_SINGLE_QUOTE && !is_in_double_quotes)
			is_in_single_quotes = !is_in_single_quotes;
		else if (**end == T_DOUBLE_QUOTE && !is_in_single_quotes)
			is_in_double_quotes = !is_in_double_quotes;
		else if (!is_in_single_quotes && !is_in_double_quotes
			&& ft_strchr(sep, **end))
		{
			set_curr_tok_type(end, tok);
			break ;
		}
		(*end)++;
	}
}

static char	*get_tok(char **stash, const char *sep, t_tok *tok)
{
	char	*start;
	char	*end;

	start = *stash;
	if ((*start) == '\0')
	{
		(*stash) = start;
		return (NULL);
	}
	update_end(start, &end, sep, tok);
	if ((*end))
	{
		if ((*end) == '|')
			(*tok) = T_PIPE;
		(*end) = '\0';
		(*stash) = (end + 1);
	}
	else
		(*stash) = end;
	return (start);
}

char	*smart_strtok(char *str, const char *sep, t_tok *tok)
{
	static char	*pipe_stash;
	static char	*redir_stash;

	if (ft_strnstr(sep, "|", 1))
	{
		if (str)
			pipe_stash = str;
		else
			(*tok) = T_NO_TOK;
		if (!pipe_stash || *pipe_stash == '\0')
			return (NULL);
		return (get_tok(&pipe_stash, sep, tok));
	}
	if (str)
		redir_stash = str;
	else
		(*tok) = T_NO_TOK;
	if (!redir_stash || *redir_stash == '\0')
		return (NULL);
	return (get_tok(&redir_stash, sep, tok));
}
