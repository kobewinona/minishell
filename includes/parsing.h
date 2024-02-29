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
t_cmd	*constr_exec_cmd(t_msh **msh, char *input);
t_cmd	*constr_pipe_cmd(t_msh **msh, t_cmd *cmd1, t_cmd *cmd2);
t_cmd	*constr_redir_cmd(t_msh **msh, t_types r_type, t_cmd *subcmd, char *f);
int		prepare_fd(t_msh **msh, t_types redir_type, int mode, char **f);
void	*cleanup_cmds(t_cmd **cmd);

t_cmd	*parse_cmd(t_msh **msh, char *input);
t_cmd	*parse_exec(t_msh **msh, char *input, t_types *tok);
char	*collect_heredoc_input(t_msh **msh, const char *eof);
char	*smart_strtok(char *restrict str,
			const char *restrict sep, t_types *tok);

int		populate_argv(t_msh **msh, char **argv, char *input);
char	*get_value(t_msh **msh, char **s);
int		get_arb_fd(char **s);

#endif
