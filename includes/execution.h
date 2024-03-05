/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:58:35 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/04 16:28:07 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

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
	int			exit_code;
	t_var_node	*env_vars;
	char		*script_name;
	t_cmd		*cmd;
	bool		is_parent;
	int			chld_pid;
}	t_msh;

// functions
int			run_cmd(t_msh **msh, t_cmd *cmd);
void		handle_ext_cmd(t_msh **msh, char **argv);
void		handle_cd(const char *input, t_var_node *env_vars);
int			handle_exec(t_msh **msh, t_exec *cmd);
int			handle_pipe(t_msh **msh, t_pipe *cmd);
int			handle_redir(t_msh **msh, t_redir *cmd);

// dollar expansion
void		expand_dollar(char **arg, t_var_node *env_vars, t_msh **msh);
bool		is_char_there(char *arg, char c);
char		*ft_strslice(const char *str, int start, int end);
int			ft_ind_char(const char *str, char c);
void		replace_dollar_sign(char **argv, t_var_node *env_vars, t_msh **msh);

// working with ENV
t_var_node	*create_var_node(char *key_val_str);
void		append_var_node(t_var_node **head, char *key_val_str);
char		*get_env_var(t_var_node *head, char *varname);
void		set_var_deleted(t_var_node *head, char *varname);
void		update_var(t_var_node *head, char *varname, char *value);
t_var_node	*copy_env_vars(char **envp);
char		**envlist_to_arr(t_var_node *env_vars);
void		increment_shlvl(t_var_node *env_vars);
bool		is_var_deleted(t_var_node *env_vars, char *varname);

// -src/builtins
void		echo(char **argv, t_msh **msh);
void		cd(char *path, t_msh **msh);
void		pwd(t_msh **msh);
void		export(char **argv, t_msh **msh);
void		unset(char **argv, t_msh **msh);
void		exit_cmd(char **argv, t_msh **msh);
void		env_cmd(char **argv, t_msh **msh);

//Signals

void track_signals(bool is_child);
#endif
