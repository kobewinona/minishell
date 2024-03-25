/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:13:52 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/25 11:41:05 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 199309L
# include "../libs/libft/includes/libft.h"
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <stdint.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include "constants.h"

// @attention global state
extern int				g_state;

// @typedef cmd structs
typedef struct s_cmd	t_cmd;

// @typedef env vars
typedef struct s_env
{
	char			*name;
	char			*value;
	bool			is_deleted;
	bool			is_value_assigned;
	struct s_env	*next;
}	t_env;

typedef struct s_exec
{
	char	*argv[MAX_INPUT + 1];
}	t_exec;

typedef struct s_pipe
{
	t_cmd	*from;
	t_cmd	*to;
}	t_pipe;

typedef struct s_redir
{
	t_redir_t	type;
	t_cmd		*subcmd;
	int			fd[2];
	char		*f;
	int			mode;
}	t_redir;

struct s_cmd
{
	t_cmd_t	type;
	union
	{
		t_exec	exec;
		t_pipe	pipe;
		t_redir	redir;
	};
};

// @typedef parsing struct
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
	char	*name;
	char	*value;
	char	end_char;
	bool	is_in_quotes;
	bool	is_redir;
}	t_ctx;

typedef struct s_evar
{
	char	*name;
	char	*value;
	bool	is_to_append;
}	t_evar;

// @typedef minishell struct
typedef struct s_msh
{
	char	*input;
	int		exit_code;
	t_env	*env_vars;
	t_cmd	*cmd;
	int		curr_pid;
	int		org_stdin;
	char	*prompt;
}	t_msh;

// @defgroup cleanup
void	cleanup_env_list(t_env *env_vars);
void	cleanup_cmds(t_cmd **cmd);
void	cleanup(t_msh **msh);

// @defgroup errors
void	handle_err(t_msh **msh, t_err err, char *ctx, int exit_code);

// @defgroup exit
void	handle_exit(t_msh **msh, int exit_code, bool is_safe);

// @defgroup parsing
int		parse_cmd(t_msh **msh);
char	*smart_strtok(char *str, const char *sep, t_tok *tok);
int		populate_argv(t_msh **msh, char **argv, char *input);
char	*get_value(t_msh **msh, char **s);
char	*collect_heredoc_input(t_msh **msh, char *eof);

// @defgroup cmd constructors
t_cmd	*constr_exec_cmd(t_msh **msh, char *input);
t_cmd	*constr_pipe_cmd(t_msh **msh, t_cmd *cmd1, t_cmd *cmd2);
t_cmd	*constr_redir_cmd(t_msh **msh, t_redir_t type, t_cmd *subcmd, char *f);

// @defgroup fds
void	prepare_fds(t_msh **msh, t_cmd **cmd);
int		get_arb_fd(char **s);

// @defgroup cmd execution
void	run_cmd(t_msh **msh, t_cmd *cmd);
void	handle_exec(t_msh **msh, t_exec *cmd);
void	handle_pipe(t_msh **msh, t_pipe *cmd);
void	handle_redir(t_msh **msh, t_redir *cmd);

// @defgroup env vars
int		exp_env_vars(t_msh **msh, char **input);
t_env	*create_var_node(char *name, char *value);
void	append_var_node(t_env **head, char *name, char *value);
char	*get_env_var(t_env *head, char *varname);
void	set_var_deleted(t_env *head, char *varname);
void	update_var(t_env *head, t_evar evar);
t_env	*copy_env_vars(t_msh **msh, char **envp);
char	**envlist_to_arr(t_env *env_vars);
void	increment_shlvl(t_msh **msh, t_env *env_vars);
bool	is_var_deleted(t_env *env_vars, char *varname);
void	update_var_value(t_env *head, t_evar evar);
bool	is_in_env(t_env *head, char *varname);

// @defgroup builtins
void	echo(char **argv, t_msh **msh);
void	cd(char **argv, t_msh **msh);
void	pwd(t_msh **msh);
void	export(char **argv, t_msh **msh);
void	unset(char **argv, t_msh **msh);
void	exit_cmd(char **argv, t_msh **msh);
void	env_cmd(char **argv, t_msh **msh);

// @defgroup signals
int		init_signals(t_msh **msh);
int		setup_signal(int signum, void (*handler)(int));

// @defgroup prompt
void	put_prompt(t_msh **msh);
int		update_prompt(t_msh **msh, char **argv, int i);

// @defgroup utils
void	free_double_array(char **arr);
bool	is_emptystr(const char *s);
void	update_exit_code(t_msh **msh, int exit_code);
char	*char_to_str(char *s);
char	*tokstr(t_tok tok);

#endif
