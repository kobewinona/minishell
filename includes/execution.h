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

// types
typedef enum e_cmd_type
{
	EXEC_CMD,
	PIPE_CMD,
	REDIR_CMD,
	HEREDOC,
}	t_cmd_type;

typedef enum e_redir_type
{
	REDIR_STDOUT,
	REDIR_STDIN,
	APPEND_STDOUT,
}	t_redir_type;

// structs
typedef struct s_cmd
{
	t_cmd_type	type;
	union
	{
		struct s_exec		*exec;
		struct s_pipe		*pipe;
		struct s_redir		*redir;
		struct s_heredoc	*heredoc;
	};
}	t_cmd;

typedef struct s_exec
{
	char	**argv;
}	t_exec;

typedef struct s_pipe
{
	t_cmd	*from;
	t_cmd	*to;
}	t_pipe;

typedef struct s_redir
{
	t_redir_type	type;
	t_cmd			*subcmd;
	char			*file;
	int				mode;
}	t_redir;

typedef struct s_heredoc
{
	t_cmd			*subcmd;
	char			*eof;
}	t_heredoc;

typedef enum e_err_type
{
	SYSTEM_ERR = 0,
	SYNTAX_ERR = 2,
	CMD_NOT_FOUND = 127,
}	t_err_type;

typedef struct s_err
{
	t_err_type	type;
	char		*context1;
	char		*context2;
}	t_err;

// functions
void		run_cmd(t_cmd *cmd);
void		handle_ext_cmd(char **argv);
void		handle_cd(const char *input);
void		handle_exec(t_exec *params);
void		handle_pipe(t_pipe *params);
void		handle_redir(t_redir *params);
void		handle_heredoc(t_heredoc *params, int output_fd);

int			handle_err(int res, t_err err, int is_on_exit);

// -src/int_cmds
void		echo(char **argv);
void		cd(char *path);
void		pwd(void);

#endif
