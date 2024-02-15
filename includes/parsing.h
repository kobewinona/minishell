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

// error messages
# define CMD_NOT_FOUND_MSG "command not found"
# define UNEXPECTED_TOK_MSG "syntax error near unexpected token"
# define UNEXPECTED_EOF_MSG "unexpected EOF while looking for matching"

// constructors
t_cmd	*constr_cmd(t_types cmd_type);
t_cmd	*constr_exec_cmd(char *input);
t_cmd	*constr_pipe_cmd(t_cmd *cmd1, t_cmd *cmd2);
t_cmd	*constr_redir_cmd(t_types redir_type, t_cmd *subcmd, char *file);
t_cmd	*constr_heredoc_cmd(t_cmd *subcmd, char *eof);
void	cleanup_cmd(t_cmd *cmd);

t_cmd	*parse_cmd(char *input);
char	*smart_strtok(char *restrict str,
			const char *restrict sep, t_types *tok);

void	populate_argv(char **argv, char *input);
char	*get_value(char **s);

#endif
