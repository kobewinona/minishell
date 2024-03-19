/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:53:48 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/20 02:30:20 by dklimkin         ###   ########.fr       */
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
# define RW_R_R_PERM 0644 // -rw-r--r-- permission settings

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
# define SIG "sigaction"
# define EXPORT "export"

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
	T_SYS_ERR,
	T_BAD_REQUEST_ERR = 1,
	T_BAD_REQUEST_ERR_PERM = 13,
	T_OTHER_ERR = 2,
	T_CMD_NOT_FOUND = 127,
	T_CMD_NOT_EXECUTABLE = 126,
	T_VAR_EXP = 36,
	T_SPACE = 32,
	T_UNDERSCORE = 95,
	T_QUESTION_MARK = 63,
}	t_types;

#endif
