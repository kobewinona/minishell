/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:53:48 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/23 05:12:04 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define PRG_NAME "minishell"

// @defgroup readline prompts
# define PRG_PROMPT "minishell> "
# define INPUT_PROMPT "> "

// @defgroup global state values
# define IS_IDLE 1
# define IS_IN_EXEC 2
# define IS_IN_HEREDOC 3

// @defgroup magic numbers
# define UNSPECIFIED -2
# define ERROR -1
# define SUCCESS 0
# define RW_R_R_PERM 0644 // -rw-r--r-- permission settings

// @defgroup custom error messages
# define CMD_NOT_FOUND_MSG "command not found"
# define UNEXPECTED_TOK_MSG "syntax error near unexpected token"
# define UNEXPECTED_EOF_TOK_MSG "unexpected EOF while looking for matching"
# define INVALID_IDENTIFIER_MSG "not a valid identifier"
# define INVALID_EXIT_ARG_MSG "numeric argument required"
# define TOO_MANY_ARGS_MSG "too many arguments"
# define INVALID_OPTION_MSG "invalid option"
# define AMBIGUOUS_REDIRECT_MSH "ambiguous redirect"

// @defgroup builtins' names
# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

// @defgroup system calls names
# define FORK "fork"
# define DUP "dup"
# define DUP2 "dup2"
# define PIPE "pipe"

// @defgroup other
# define MALLOC "malloc"

// @defgroup command types
typedef enum e_cmd_t
{
	C_EXEC,
	C_PIPE,
	C_REDIR,
}	t_cmd_t;

// @defgroup redirection types
typedef enum e_redir_t
{
	R_STDIN = 1,
	R_STDOUT = 2,
	R_APPEND = 3,
	R_HEREDOC = 4,
}	t_redir_t;

// @defgroup token types
typedef enum e_tok
{
	T_NO_TOK = 0,
	T_PIPE = 124,
	T_R_STDIN = 1,
	T_R_STDOUT = 2,
	T_R_APPEND = 3,
	T_R_HEREDOC = 4,
	T_DOUBLE_QUOTE = 34,
	T_SINGLE_QUOTE = 39,
	T_SPACE = 32,
}	t_tok;

// @enum error types
typedef enum e_err
{
	SYSTEM,
	NO_FILE_OR_DIR = 2,
	CD_NO_FILE_OR_DIR,
	PERM_DENIED = 13,
	CD_PERM_DENIED,
	CMD_IS_DIR = 21,
	CMD_NOT_FOUND,
	CD_INVALID_OPTION,
	UNEXPECTED_TOK,
	UNEXPECTED_EOF,
	EXPORT_INVALID_IDENTIFIER,
	UNSET_INVALID_IDENTIFIER,
	EXIT_INVALID_ARG,
	TOO_MANY_ARGS,
	AMBGIGUOUS_R,
}	t_err;

#endif
