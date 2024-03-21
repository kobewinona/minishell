/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:53:48 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 11:12:03 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define PRG_NAME "minishell"
# define INPUT_PROMPT "> "
# define PRG_PROMPT "minishell> "

# define IS_IDLE 1
# define IS_EXEC 2
# define IS_HEREDOC 3

// magic numbers
# define UNSPECIFIED -2
# define ERROR -1
# define SUCCESS 0
# define RW_R_R_PERM 0644 // -rw-r--r-- permission settings

// custom error messages
# define CMD_NOT_FOUND_MSG "command not found"
# define UNEXPECTED_TOK_MSG "syntax error near unexpected token"
# define UNEXPECTED_EOF_TOK_MSG "unexpected EOF while looking for matching"
# define NO_FILE_OR_DIR_MSG "No such file or directory"
# define EXIT_INVALID_EXPORT_ARG_MSG1 "numeric argument required"
# define BAD_SUBST_MSG "bad substitution"
# define INVALID_EXPORT_ARG_MSG "not a valid identifier"
# define INVALID_EXIT_ARG_MSG "numberic argument required"
# define TOO_MANY_ARGS_MSG "too many arguments"

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
# define PIPE "pipe"
# define MALLOC "malloc"
# define NEWLINE "newline"

// types
typedef enum e_types
{
	T_NO_TOK,
	T_EXEC,
	T_PIPE = 124,
	T_BRACKET_OPEN = 40,
	T_BRACKET_CLOSE = 41,
	T_CURLY_OPEN = 123,
	T_CURLY_CLOSE = 125,
	T_SQUARE_OPEN = 91,
	T_SQUARE_CLOSE = 93,
	T_REDIR,
	T_HEREDOC,
	T_REDIR_STDOUT = 62,
	T_REDIR_STDIN = 60,
	T_APPEND_STDOUT,
	T_DOUBLE_QUOTE = 34,
	T_SINGLE_QUOTE = 39,
	T_VAR_EXP = 36,
	T_SPACE = 32,
	T_UNDERSCORE = 95,
	T_QUESTION_MARK = 63,
}	t_types;

typedef enum e_err
{
	SYSTEM,
	BAD_REQUEST,
	NO_FILE_OR_DIR = 2,
	CD_NO_FILE_OR_DIR,
	PERM_DENIED = 13,
	CD_PERM_DENIED,
	CMD_IS_DIR = 21,
	CMD_NOT_FOUND,
	UNEXPECTED_TOK,
	UNEXPECTED_EOF,
	EXPORT_INVALID_ARG,
	EXIT_INVALID_ARG,
	TOO_MANY_ARGS,
}	t_err;

#endif
