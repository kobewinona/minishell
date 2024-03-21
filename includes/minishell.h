/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:13:52 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 08:07:42 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 199309L
# include "../libs/libft/includes/libft.h"
# include "constants.h"
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <stdint.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include "execution.h"
# include "parsing.h"

// utils
bool	is_emptystr(const char *s);
char	*tokstr(t_types tok);
void	free_array(char **arr);
void	update_exit_code(t_msh **msh, int encoded_exit_code);

#endif
