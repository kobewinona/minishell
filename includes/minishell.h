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
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <string.h>

# define SUCCESS 1
# define ERROR 2

// types

typedef enum e_cmd_type
{
	EXEC,
	PIPE,
	REDIR,
}	t_cmd_type;

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
	t_cmd	*subcmd;
	char	*file;
	int		mode;
	int		fd;
}	t_redir;

// functions
// -src

void	exec_cmd(t_cmd *cmd);
void	handle_exit(int is_on_error);

// -src/commands

//int		echo(char *args);

#endif
