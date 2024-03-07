/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:55:37 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/04 16:28:16 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

// error messages
# define CMD_NOT_FOUND_MSG "command not found"
# define CMD_FOUND_NOT_EXEC_MSG "permission denied"
# define UNEXPECTED_TOK_MSG "syntax error near unexpected token"
# define UNEXPECTED_EOF_MSG "unexpected EOF while looking for matching"
# define NO_FILE_OR_DIR_MSG "No such file or directory"
# define EXIT_INVALID_ARG_MSG1 "numeric argument required"
# define EXPORT_INVALID_ARG_MSG1 "not a valid identifier"

// parsing
t_cmd	*parse_cmd(t_msh **msh, char *input);
t_cmd	*parse_exec(t_msh **msh, char *input, t_types *tok);

char	*smart_strtok(char *str, const char *sep, t_types *tok);
int		populate_argv(t_msh **msh, char **argv, char *input);
char	*get_value(t_msh **msh, char **s);
ssize_t	exp_env_var(t_msh **msh, char **value, char *s, char end_char);
int		get_arb_fd(char **s);
char	*collect_heredoc_input(t_msh **msh, const char *eof);

// fd handlers
void	prepare_fds(t_msh **msh, t_cmd **cmd);

// constructors
t_cmd	*constr_exec_cmd(t_msh **msh, char *input);
t_cmd	*constr_pipe_cmd(t_msh **msh, t_cmd *cmd1, t_cmd *cmd2);
t_cmd	*constr_redir_cmd(t_msh **msh, t_types r_type, t_cmd *subcmd, char *f);
void	cleanup_cmds(t_cmd **cmd);

#endif
