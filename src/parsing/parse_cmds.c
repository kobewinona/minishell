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

char	*collect_heredoc_input(const char *eof)
{
	char	*heredoc_input;
	char	*tty_input;
	char	*temp;

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

static t_cmd	*parse_exec(char *input, t_types *tok, t_var_node *env_vars)
{
	t_cmd	*cmd;
	char	*s;
	t_types	prev_tok;

	cmd = NULL;
	s = NULL;
	if (*tok == T_NO_TOK || *tok == T_PIPE)
		cmd = constr_exec_cmd(input, env_vars);
	else
	{
		prev_tok = *tok;
		s = smart_strtok(NULL, "><", tok);
		if (s && is_emptystr(s))
			handle_err(ERROR, (t_err){T_SYNTAX_ERR,
				UNEXPECTED_TOK_MSG, tokstr(*tok)}, true);
		if (prev_tok == T_HEREDOC)
			cmd = constr_redir_cmd(prev_tok, parse_exec(input, tok, env_vars),
					collect_heredoc_input(get_value(&s)));
		else
			cmd = constr_redir_cmd(prev_tok,
					parse_exec(input, tok, env_vars), get_value(&s));
		if (s && !is_emptystr(s) && cmd->redir.subcmd->type == T_EXEC)
			populate_argv(cmd->redir.subcmd->exec.argv, s);
	}
	return (cmd);
}

static t_cmd	*parse_pipe(char *input, t_types *tok, t_var_node *env_vars)
{
	t_cmd	*cmd;
	char	*s;
	t_types	prev_tok;

	s = NULL;
	cmd = parse_exec(smart_strtok(input, "><", tok), tok, env_vars);
	prev_tok = *tok;
	s = smart_strtok(NULL, "|", tok);
	if (s)
		cmd = constr_pipe_cmd(cmd, parse_pipe(s, tok, env_vars));
	if ((!s || is_emptystr(s)) && prev_tok == T_PIPE)
		handle_err(ERROR, (t_err){T_SYNTAX_ERR,
			UNEXPECTED_TOK_MSG, tokstr(prev_tok)}, true);
	return (cmd);
}

t_cmd	*parse_cmd(char *input, t_var_node *env_vars)
{
	t_cmd		*cmd;
	t_types		tok;
	char		*s;

	tok = T_NO_TOK;
	s = NULL;
	s = smart_strtok(input, "|", &tok);
	if (is_emptystr(s))
		handle_err(ERROR, (t_err){T_SYNTAX_ERR,
			UNEXPECTED_TOK_MSG, tokstr(tok)}, true);
	cmd = parse_pipe(s, &tok, env_vars);
	return (cmd);
}
