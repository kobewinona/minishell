/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:51:53 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/25 12:46:09 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		populate_argv(t_msh **msh, char **argv, char *input);

t_cmd	*parse_exec(t_msh **msh, char *input, t_tok *tok);

static t_cmd	*parse_redir(t_msh **msh, char *input, char **s, t_tok *tok)
{
	t_cmd	*cmd;
	t_cmd	*subcmd;
	t_tok	prev_tok;
	int		arb_fd;

	cmd = NULL;
	prev_tok = *tok;
	arb_fd = UNSPECIFIED;
	*s = smart_strtok(NULL, "><", tok);
	arb_fd = get_arb_fd(&input);
	if (!(*s) || is_emptystr(*s))
		return (handle_err(msh, UNEXPECTED_TOK, "newline", 2), NULL);
	subcmd = parse_exec(msh, input, tok);
	cmd = constr_redir_cmd(msh, (t_redir_t)prev_tok, subcmd, get_value(msh, s));
	if (cmd)
		cmd->redir.fd[1] = arb_fd;
	return (cmd);
}

t_cmd	*parse_exec(t_msh **msh, char *input, t_tok *tok)
{
	t_cmd	*cmd;
	char	*s;

	cmd = NULL;
	s = NULL;
	if (*tok == T_NO_TOK || *tok == T_PIPE)
		cmd = constr_exec_cmd(msh, input);
	else
	{
		cmd = parse_redir(msh, input, &s, tok);
		if (!cmd)
			return (NULL);
		if (s && !is_emptystr(s) && cmd->redir.subcmd->type == C_EXEC)
		{
			if (populate_argv(msh, cmd->redir.subcmd->exec.argv, s) == ERROR)
				return (NULL);
		}
	}
	return (cmd);
}

static t_cmd	*parse_pipe(t_msh **msh, char *input, t_tok *tok)
{
	t_cmd	*cmd;
	char	*s;
	t_tok	prev_tok;

	cmd = NULL;
	s = NULL;
	cmd = parse_exec(msh, smart_strtok(input, "><", tok), tok);
	prev_tok = *tok;
	s = smart_strtok(NULL, "|", tok);
	if ((!s || is_emptystr(s)) && (*tok) == T_PIPE)
		return (handle_err(msh, UNEXPECTED_TOK, tokstr(prev_tok), 2), NULL);
	if (s)
		cmd = constr_pipe_cmd(msh, cmd, parse_pipe(msh, s, tok));
	return (cmd);
}

int	parse_cmd(t_msh **msh)
{
	t_tok	tok;
	char	*s;

	if (is_emptystr((*msh)->input))
		return (ERROR);
	if (exp_env_vars(msh, &((*msh)->input)) == ERROR)
		return (ERROR);
	(*msh)->cmd = NULL;
	tok = T_NO_TOK;
	s = NULL;
	s = smart_strtok((*msh)->input, "|", &tok);
	if (is_emptystr(s) && tok != T_NO_TOK)
		return (handle_err(msh, UNEXPECTED_TOK, tokstr(tok), 2), ERROR);
	if (!is_emptystr(s))
		(*msh)->cmd = parse_pipe(msh, s, &tok);
	return (SUCCESS);
}
