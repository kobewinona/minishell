/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:51:53 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/06 18:51:54 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*collect_heredoc_input(t_msh **msh, const char *eof)
{
	char	*heredoc_input;
	char	*tty_input;
	char	*temp;

	if (!eof)
	{
		log_err(msh, T_SYNTAX_ERR, UNEXPECTED_TOK_MSG, NEWLINE);
		return (NULL);
	}
	heredoc_input = ft_strdup("");
	tty_input = readline(INPUT_PROMPT);
	while (tty_input)
	{
		if (!ft_strncmp(tty_input, eof, ft_strlen(eof)))
			break ;
		temp = ft_strjoin(heredoc_input, tty_input);
		free(heredoc_input);
		heredoc_input = temp;
		temp = ft_strjoin(heredoc_input, "\n");
		free(heredoc_input);
		heredoc_input = temp;
		free(tty_input);
		tty_input = readline(INPUT_PROMPT);
	}
	free(tty_input);
	return (heredoc_input);
}

static t_cmd	*parse_exec(t_msh **msh, char *input, t_types *tok)
{
	t_cmd	*cmd;
	char	*s;
	t_types	prev_tok;

	s = NULL;
	if (*tok == T_NO_TOK || *tok == T_PIPE)
		cmd = constr_exec_cmd(msh, input);
	else
	{
		prev_tok = *tok;
		s = smart_strtok(NULL, "><", tok);
		if (s && is_emptystr(s))
		{
			log_err(msh, T_SYNTAX_ERR, UNEXPECTED_TOK_MSG, tokstr(*tok));
			return (NULL);
		}
		if (prev_tok == T_HEREDOC)
			cmd = constr_redir_cmd(msh, prev_tok, parse_exec(msh, input, tok),
					collect_heredoc_input(msh, get_value(msh, &s)));
		else
			cmd = constr_redir_cmd(msh, prev_tok,
					parse_exec(msh, input, tok), get_value(msh, &s));
		if (s && !is_emptystr(s) && cmd->redir.subcmd->type == T_EXEC)
		{
			if (populate_argv(msh, cmd->redir.subcmd->exec.argv, s) == ERROR)
				return (NULL);
		}
	}
	return (cmd);
}

static t_cmd	*parse_pipe(t_msh **msh, char *input, t_types *tok)
{
	t_cmd	*cmd;
	char	*s;
	t_types	prev_tok;

	s = NULL;
	cmd = parse_exec(msh, smart_strtok(input, "><", tok), tok);
	prev_tok = *tok;
	s = smart_strtok(NULL, "|", tok);
	if (s)
		cmd = constr_pipe_cmd(msh, cmd, parse_pipe(msh, s, tok));
	if ((!s || is_emptystr(s)) && prev_tok == T_PIPE)
	{
		log_err(msh, T_SYNTAX_ERR, UNEXPECTED_TOK_MSG, tokstr(prev_tok));
		return (NULL);
	}
	return (cmd);
}

t_cmd	*parse_cmd(t_msh **msh, char *input)
{
	t_cmd		*cmd;
	t_types		tok;
	char		*s;

	tok = T_NO_TOK;
	s = NULL;
	s = smart_strtok(input, "|", &tok);
	if (is_emptystr(s))
	{
		log_err(msh, T_SYNTAX_ERR, UNEXPECTED_TOK_MSG, tokstr(tok));
		return (NULL);
	}
	cmd = parse_pipe(msh, s, &tok);
	return (cmd);
}
