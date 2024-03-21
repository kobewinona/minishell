/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:58:35 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 11:20:04 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

extern int				g_state;

// structs
typedef struct s_var_node
{
	char				*name;
	char				*value;
	char				*key_val_str;
	bool				is_numeric;
	bool				deleted;
	bool				value_assigned;
	struct s_var_node	*next;
}	t_var_node;

typedef struct s_cmd	t_cmd;

typedef struct s_exec
{
	char		*argv[MAX_INPUT + 1];
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
	int		fd[2];
	char	*f;
	int		mode;
}	t_redir;

struct s_cmd
{
	t_types	type;
	union
	{
		t_exec		exec;
		t_pipe		pipe;
		t_redir		redir;
	};
};

typedef struct s_msh
{
	char		*input;
	int			exit_code;
	t_var_node	*env_vars;
	char		*script_name;
	t_cmd		*cmd;
	int			curr_pid;
	int			org_fd;
	char		*prompt;
}	t_msh;

// cleanup
void		cleanup(t_msh **msh);
void		handle_exit(t_msh **msh, int exit_code, bool is_safe);

// cmd execution
void		run_cmd(t_msh **msh, t_cmd *cmd);
void		handle_exec(t_msh **msh, t_exec *cmd);
void		handle_pipe(t_msh **msh, t_pipe *cmd);
void		handle_redir(t_msh **msh, t_redir *cmd);

// env
t_var_node	*create_var_node(char *key_val_str);
void		append_var_node(t_var_node **head, char *key_val_str);
char		*get_env_var(t_var_node *head, char *varname);
void		set_var_deleted(t_var_node *head, char *varname);
void		update_var(t_var_node *head, char *varname, char *value);
t_var_node	*copy_env_vars(char **envp);
char		**envlist_to_arr(t_var_node *env_vars);
void		increment_shlvl(t_var_node *env_vars);
bool		is_var_deleted(t_var_node *env_vars, char *varname);
void		free_envlist(t_var_node *env_vars);
void		update_var_value(t_var_node *head, char *varname, char *new_val);
bool		is_in_env(t_var_node *head, char *varname);

// builtins
void		echo(char **argv, t_msh **msh);
void		cd(char *path, t_msh **msh);
void		pwd(t_msh **msh);
void		export(char **argv, t_msh **msh);
void		unset(char **argv, t_msh **msh);
void		exit_cmd(char **argv, t_msh **msh);
void		env_cmd(char **argv, t_msh **msh);

// signals
int			init_signals(t_msh **msh);
int			setup_signal(int signum, void (*handler)(int));

// errors
void		handle_err(t_msh **msh, t_err err, char *ctx, int exit_code);

// prompt
void		put_prompt(t_msh **msh);
int			update_prompt(t_msh **msh, char **argv, int i);

#endif
