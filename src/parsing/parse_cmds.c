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

t_cmd	*parse_redir(char *s, t_types *tok)
{
	t_cmd	*cmd;
	char	*file;
	t_types	redir_type;

	if (*tok != T_NO_TOK && *tok != T_PIPE)
	{
		redir_type = *tok;
		s = smart_strtok(NULL, "><", tok);
		file = get_value(&s);
		cmd = constr_redir_cmd(redir_type, NULL, file);
	}
	return (cmd);
}

t_cmd	*parse_exec(char *input, t_types *tok)
{
	t_cmd	*cmd;

	if (*tok == T_NO_TOK || *tok == T_PIPE)
		cmd = constr_exec_cmd(input);
	else
	{
		cmd = parse_redir(input, tok);
		cmd->redir.subcmd = parse_exec(input, tok);
	}
	return (cmd);
}

t_cmd	*parse_pipe(char *input, t_types *tok)
{
	t_cmd	*cmd;
	char	*s;

	cmd = parse_exec(smart_strtok(input, "><", tok), tok);
	s = smart_strtok(NULL, "|", tok);
	if (s)
		cmd = constr_pipe_cmd(cmd, parse_pipe(s, tok));
	return (cmd);
}

// TODO maybe add handling of `ls |`
t_cmd	*parse_cmd(char *input)
{
	t_cmd		*cmd;
	t_types		tok;
	char		*s;

	tok = T_NO_TOK;
	s = smart_strtok(input, "|", &tok);
	if (is_emptystr(s))
		handle_err(ERROR, (t_err){T_SYNTAX_ERR,
			UNEXPECTED_TOK_MSG, tokstr(tok)}, true);
	cmd = parse_pipe(s, &tok);
	return (cmd);
}
