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

typedef struct s_var_node
{
	char				*name;
	char				*value;
	char				*key_val_str;
	bool				is_numeric;
	bool				deleted;
	struct s_var_node	*next;

}	t_var_node;


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
void		run_cmd(t_cmd *cmd, t_var_node *env_vars);
void	handle_ext_cmd(char **argv, t_var_node *env_vars);
void		handle_cd(const char *input, t_var_node *env_vars);
void		handle_exec(t_exec *cmd, t_var_node *env_vars);
void		handle_pipe(t_pipe *cmd, t_var_node *env_vars);
void		handle_redir(t_redir *cmd, t_var_node *env_vars);
void		handle_heredoc(t_heredoc *cmd, int output_fd, t_var_node *env_vars);

int			handle_err(int res, t_err err, bool is_on_exit);
void   		handle_builtin(t_exec *params, t_var_node *env_vars);


//dolar expansion 
void    expand_dollar(char **arg, t_var_node *env_vars);
bool    is_char_there(char *arg, char c);
char 	*ft_strslice(const char  *str, int start, int end);
int 	ft_ind_char(const char *str, char c);
void    free_array(char **arr);
void    replace_dollar_sign(char **argv, t_var_node *env_vars);

//working with ENV
t_var_node  *create_var_node(char *key_val_str);
void		append_var_node(t_var_node **head, char *key_val_str);
char   		*get_env_var(t_var_node *head, char *varname);
void   		set_var_deleted(t_var_node *head, char *varname);
void 		update_var(t_var_node *head, char *varname, char *value);
t_var_node  *copy_env_vars(char **envp);
char		**envlist_to_arr(t_var_node *env_vars);


// -src/int_cmds
void	echo(char **argv, t_var_node *env_vars);
void	cd(char *path, t_var_node *env_vars);
void	pwd(t_var_node *env_vars);
void    export(char **argv, t_var_node *env_vars);
void    unset(char **argv, t_var_node *env_vars);
void	exit_cmd(char **argv);

#endif
