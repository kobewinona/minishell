/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:55:37 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/06 19:55:38 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

// ls -l > ls.txt < sort -n | cat

typedef enum e_tok
{
	NO_TOK,
	PIPE_TOK,
	REDIR_STDOUT_TOK,
	REDIR_STDIN_TOK,
	APPEND_STDOUT_TOK,
	HEREDOC_TOK,
}	t_tok;

typedef struct s_tok_info
{
	t_tok	curr_tok;
}	t_tok_info;

// constructors
t_cmd	*constr_exec_cmd(char *input);
t_cmd	*constr_pipe_cmd(t_cmd *cmd1, t_cmd *cmd2);
t_cmd	*constr_redir_cmd(t_redir_type type, t_cmd *subcmd, char *file);
t_cmd	*constr_heredoc_cmd(t_cmd *subcmd, char *eof);

t_cmd	*parse_cmd(char *input);
char	*smart_strtok(char *restrict str,
			const char *restrict sep, t_tok *tok_info);

#endif
