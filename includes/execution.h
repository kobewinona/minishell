/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:58:35 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/06 18:58:35 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

// structs
typedef struct s_cmd	t_cmd;

typedef struct s_exec
{
	char	*argv[MAX_INPUT + 1];
	char	**envp;
}	t_exec;

typedef struct s_pipe
{
	t_cmd	*from;
	t_cmd	*to;
}	t_pipe;

typedef struct s_redir
{
	t_types	type;
	t_cmd	*subcmd;
	char	*file;
	int		mode;
}	t_redir;

typedef struct s_heredoc
{
	t_cmd			*subcmd;
	char			*eof;
}	t_heredoc;

struct s_cmd
{
	t_types	type;
	union
	{
		t_exec		exec;
		t_pipe		pipe;
		t_redir		redir;
		t_heredoc	heredoc;
	};
};

typedef struct s_err
{
	t_types	type;
	char	*ctx1;
	char	*ctx2;
}	t_err;

// functions
void		run_cmd(t_cmd *cmd);
void		handle_ext_cmd(char **argv);
void		handle_cd(const char *input);
void		handle_exec(t_exec *cmd);
void		handle_pipe(t_pipe *cmd);
void		handle_redir(t_redir *cmd);
void		handle_heredoc(t_heredoc *cmd, int output_fd);

int			handle_err(int res, t_err err, bool is_on_exit);

// -src/int_cmds
void		echo(char **argv);
void		cd(char *path);
void		pwd(void);

#endif
