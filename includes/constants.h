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

// @ int_cmds = internal commands implemented in this project
// @ ext_cmds = external builtin commands

# define NAME "minishell"
# define PROMPT "> "

// magic numbers
# define ERROR -1
# define RW_R_R_PERM 0644 // -rw-r--r-- permission settings
# define RW_RW_RW_PERM 0666 // -rw-r--r-- permission settings

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

// error messages
# define CMD_NOT_FOUND "Command not found\n"

#endif
