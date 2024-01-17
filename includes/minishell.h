/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:13:52 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/10 14:13:53 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <string.h>

// @ int_cmds = internal commands implemented in this project
// @ ext_cmds = external builtin commands

// magic numbers
# define ERROR -1
# define RW_R_R_PERM 0644 // -rw-r--r-- permission settings

// command names
# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

// types
typedef enum e_cmd_type
{
	EXEC,
	PIPE,
	REDIR,
}	t_cmd_type;

typedef enum e_redir_type
{
	REDIR_STD_OUT,
	REDIR_STD_IN,
	APPEND_STD_OUT,
	APPEND_STD_IN,
}	t_redir_type;

// structs
typedef struct s_cmd
{
	t_cmd_type	type;
	union
	{
		struct s_exec	*exec;
		struct s_pipe	*pipe;
		struct s_redir	*redir;
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

// functions
// -src
void	run_cmd(t_cmd *cmd);
void	handle_ext_cmd(char **argv);
void	handle_cd(const char *input);
void	handle_exec(t_exec *exec_params);
void	handle_pipe(t_pipe *pipe_params);
void	handle_redir(t_redir *redir_params);
void	handle_exit(int exit_status);

// constructors
t_cmd	*construct_exec_cmd(char **argv);
t_cmd	*construct_pipe_cmd(t_cmd *cmd1, t_cmd *cmd2);
t_cmd	*construct_redir_cmd(
			t_redir_type type, t_cmd *subcmd, char *file, int mode);

// -src/int_cmds
void	echo(char **argv);
void	cd(char *path);
void	pwd(void);

// -utils
// -utils/sys_calls
int		chdir1(const char *path); // same as chdir but with perror on error
pid_t	fork1(void); // same as fork but exits on error
int		dup3(int new_fd, int old_fd); // same as dup2 but exits on error

#endif
