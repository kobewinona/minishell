/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:55:37 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/20 22:47:40 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"

typedef struct s_val
{
	char	**s;
	size_t	len;
	int		offset;
	bool	is_in_quotes;
	char	end_char;
}	t_val;

typedef struct s_ctx
{
	char	**input;
	size_t	input_len;
	char	*s;
	int		offset;
	int		index;
	char	*name;
	char	*value;
	bool	iseof;
}	t_ctx;

// parsing
int		parse_cmd(t_msh **msh);
char	*smart_strtok(char *str, const char *sep, t_types *tok);
int		populate_argv(t_msh **msh, char **argv, char *input);
char	*get_value(t_msh **msh, char **s);
int		exp_env_var(t_msh **msh, char **input, bool is_input_enclosed);
int		get_arb_fd(char **s);
char	*collect_heredoc_input(t_msh **msh, const char *eof);

// fd handlers
int		prepare_fds(t_msh **msh, t_cmd **cmd);

// constructors
t_cmd	*constr_exec_cmd(t_msh **msh, char *input);
t_cmd	*constr_pipe_cmd(t_msh **msh, t_cmd *cmd1, t_cmd *cmd2);
t_cmd	*constr_redir_cmd(t_msh **msh, t_types r_type, t_cmd *subcmd, char *f);
void	cleanup_cmds(t_cmd **cmd);

#endif
