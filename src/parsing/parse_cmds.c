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

t_cmd	*parse_exec(char *input, t_types *tok, char **envp)
{
	t_cmd	*cmd;
	char	*s;
	char	*file;
	t_types	prev_tok;

	s = NULL;
	if (*tok == T_NO_TOK || *tok == T_PIPE)
		cmd = constr_exec_cmd(input, envp);
	else
	{
		prev_tok = *tok;
		s = smart_strtok(NULL, "><", tok);
		if (s && is_emptystr(s))
			handle_err(ERROR, (t_err){T_SYNTAX_ERR,
				UNEXPECTED_TOK_MSG, tokstr(*tok)}, true);
		file = get_value(&s);
		cmd = constr_redir_cmd(prev_tok, parse_exec(input, tok, envp), file);
		if (s && !is_emptystr(s) && cmd->redir.subcmd->type == T_EXEC)
			populate_argv(cmd->redir.subcmd->exec.argv, s);
	}
	return (cmd);
}

t_cmd	*parse_pipe(char *input, t_types *tok, char **envp)
{
	t_cmd	*cmd;
	char	*s;
	t_types	prev_tok;

	s = NULL;
	cmd = parse_exec(smart_strtok(input, "><", tok), tok, envp);
	prev_tok = *tok;
	s = smart_strtok(NULL, "|", tok);
	if (s)
		cmd = constr_pipe_cmd(cmd, parse_pipe(s, tok, envp));
	if ((!s || is_emptystr(s)) && prev_tok == T_PIPE)
		handle_err(ERROR, (t_err){T_SYNTAX_ERR,
			UNEXPECTED_TOK_MSG, tokstr(prev_tok)}, true);
	return (cmd);
}

t_cmd	*parse_cmd(char *input, char **envp)
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
	cmd = parse_pipe(s, &tok, envp);
	return (cmd);
}
