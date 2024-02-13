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

// functions
void	run_cmd(t_cmd *cmd);
void	handle_ext_cmd(char **argv);
void	handle_cd(const char *input);
void	handle_exec(t_exec *params);
void	handle_pipe(t_pipe *params);
void	handle_redir(t_redir *params);
void	handle_heredoc(t_heredoc *params, int output_fd);
int		handle_err(int res, char *cxt1, char *cxt2, int is_on_exit);

//dolar expansion 
void    expand_dollar(char **arg);
void    replace_dollar_sign(char **argv);
bool    is_char_there(char *arg, char c);
char 	*ft_strslice(const char  *str, int start, int end);
int 	ft_ind_char(const char *str, char c);

// -src/int_cmds
void	echo(char **argv);
void	cd(char *path);
void	pwd(void);

#endif
