/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:53:48 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/06 19:53:53 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define PRG_NAME "minishell"
# define INPUT_PROMPT "> "
# define PRG_PROMPT "minishell> "

// magic numbers
# define UNSPECIFIED -2
# define ERROR -1
# define SUCCESS 0
# define FAILURE 1
# define RW_R_R_PERM 0644 // -rw-r--r-- permission settings
# define RW_RW_RW_PERM 0666 // -rw-rw-rw- permission settings

// command names
# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

// system calls and functions names
# define FORK "fork"
# define DUP "dup"
# define DUP2 "dup2"
# define OPEN "open"
# define PIPE "pipe"
# define GETENV "getenv"
# define MALLOC "malloc"
# define WRITE "write"
# define NEWLINE "newline"

// types
typedef enum e_types
{
	T_NO_TOK,
	T_EXEC,
	T_PIPE = 124,
	T_REDIR,
	T_HEREDOC,
	T_REDIR_STDOUT = 62,
	T_REDIR_STDIN = 60,
	T_APPEND_STDOUT,
	T_DOUBLE_QUOTE = 34,
	T_SINGLE_QUOTE = 39,
	T_SYS_ERR,
	T_BAD_REQUEST_ERR = 1,
	T_OTHER_ERR = 2,
	T_CMD_NOT_FOUND = 127,
	T_VAR_EXP = 36,
	T_SPACE = 32,
	T_UNDERSCORE = 95,
}	t_types;

#endif
