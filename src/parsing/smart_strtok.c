/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_strtok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:53:08 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/09 12:53:09 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	set_curr_tok_type(char *token, t_tok *curr_tok)
{
	if (*token == '>')
	{
		if (*(token + 1) == '>')
		{
			*curr_tok = APPEND_STDOUT_TOK;
			(*token)++;
			return ;
		}
		*curr_tok = REDIR_STDOUT_TOK;
		return ;
	}
	if (*token == '<')
	{
		if (*(token + 1) == '<')
		{
			*curr_tok = HEREDOC_TOK;
			(*token)++;
			return ;
		}
		*curr_tok = REDIR_STDIN_TOK;
		return ;
	}
	*curr_tok = NO_TOK;
}

static void	update_end(char *start, char **end, const char *sep, t_tok *tok)
{
	bool	is_in_single_quotes;
	bool	is_in_double_quotes;
	char	*end_trimmed;

	*end = start;
	is_in_single_quotes = false;
	is_in_double_quotes = false;
	while (**end)
	{
		if (**end == '\'' && !is_in_double_quotes)
			is_in_single_quotes = !is_in_single_quotes;
		else if (**end == '\"' && !is_in_single_quotes)
			is_in_double_quotes = !is_in_double_quotes;
		else if (!is_in_single_quotes && !is_in_double_quotes
			&& ft_strchr(sep, **end))
		{
			end_trimmed = ft_strtrim(*end, " ");
			set_curr_tok_type(end_trimmed, tok);
			free(end_trimmed);
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
	while (*start && ft_strchr(sep, *start))
		start++;
	if (*start == '\0')
	{
		*stash = start;
		return (NULL);
	}
	update_end(start, &end, sep, tok);
	if (*end)
	{
		if (*end == 'c')
			*tok = PIPE_TOK;
		*end = '\0';
		*stash = end + 1;
	}
	else
		*stash = end;
	return (start);
}

char	*smart_strtok(char *restrict str,
		const char *restrict sep, t_tok *tok)
{
	static char	*pipe_stash;
	static char	*redir_stash;

	if (ft_strnstr(sep, "|", 1))
	{
		if (str)
			pipe_stash = str;
		else
			*tok = NO_TOK;
		if (!pipe_stash || *pipe_stash == '\0')
			return (NULL);
		return (get_tok(&pipe_stash, sep, tok));
	}
	if (str)
		redir_stash = str;
	else
		*tok = NO_TOK;
	if (!redir_stash || *redir_stash == '\0')
		return (NULL);
	return (get_tok(&redir_stash, sep, tok));
}
