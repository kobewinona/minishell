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

char	*parse_file(char *s)
{
	char	*file;
	char	**s_split;

	file = NULL;
	if (*s == '\"')
	{
		if (ft_strchr((s + 1), '\"'))
			file = ft_strtrim(s, "\"");
	}
	else
	{
		s_split = ft_split(s, ' ');
		if (!s_split)
			return (NULL);
		file = s_split[0];
	}
	return (file);
}

t_cmd	*parse_redir(char *s, t_tok_info *tok_info)
{
	t_cmd	*cmd;

	if (tok_info->curr_tok != NO_TOK && tok_info->curr_tok != PIPE_TOK)
	{
		if (tok_info->curr_tok == REDIR_STDOUT_TOK)
			cmd = constr_redir_cmd(REDIR_STDOUT, NULL, NULL);
		if (tok_info->curr_tok == REDIR_STDIN_TOK)
			cmd = constr_redir_cmd(REDIR_STDIN, NULL, NULL);
		if (tok_info->curr_tok == APPEND_STDOUT_TOK)
			cmd = constr_redir_cmd(APPEND_STDOUT, NULL, NULL);
		s = smart_strtok(NULL, "><", &tok_info->curr_tok);
		cmd->redir->file = parse_file(ft_strtrim(s, " "));
		return (cmd);
	}
	return (NULL);
}

t_cmd	*parse_exec(char *input, t_tok_info *tok_info)
{
	t_cmd			*cmd;

	if (tok_info->curr_tok == NO_TOK)
		cmd = constr_exec_cmd(input);
	else
	{
		cmd = parse_redir(input, tok_info);
		cmd->redir->subcmd = parse_exec(input, tok_info);
	}
	return (cmd);
}

t_cmd	*parse_pipe(char *input, t_tok_info *tok_info)
{
	t_cmd	*cmd;
	char	*s;

	cmd = parse_exec(smart_strtok(input, "><", &tok_info->curr_tok), tok_info);
	s = smart_strtok(NULL, "|", &tok_info->curr_tok);
	if (s)
        cmd = constr_pipe_cmd(cmd, parse_pipe(s, tok_info));
	return (cmd);
}

// TODO maybe add handling of `ls |`
t_cmd	*parse_cmd(char *input)
{
	t_cmd		*cmd;
	t_tok_info	tok_info;
	char		*s;

	cmd = NULL;
	tok_info.curr_tok = NO_TOK;
	s = smart_strtok(input, "|", &tok_info.curr_tok);
	cmd = parse_pipe(s, &tok_info);
	return (cmd);
}
