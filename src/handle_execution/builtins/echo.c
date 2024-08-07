/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:22 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/25 19:55:21 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_valid_n_opt(char *s) {
  int i;

  i = 0;
  if (!s || s[i++] != '-')
    return (false);
  while (s[i]) {
    if (s[i] != 'n')
      return (false);
    i++;
  }
  return (true);
}

static void handle_print(t_msh **msh, char **argv, int i,
                         bool is_with_newline) {
  if (is_with_newline) {
    if (write(STDOUT_FILENO, argv[i], ft_strlen(argv[i])) == ERROR)
      handle_exit(msh, EXIT_FAILURE, true);
    if (argv[i + 1]) {
      if (write(STDOUT_FILENO, " ", 1) == ERROR)
        handle_exit(msh, EXIT_FAILURE, true);
    }
  } else {
    if (update_prompt(msh, argv, i) == ERROR)
      handle_exit(msh, EXIT_FAILURE, true);
  }
}

void echo(char **argv, t_msh **msh) {
  bool is_with_newline;
  bool is_reading_flag;
  int i;

  i = 1;
  is_with_newline = true;
  is_reading_flag = true;
  while (argv[i]) {
    if (is_valid_n_opt(argv[i]) && is_reading_flag) {
      is_with_newline = false;
      i++;
      continue;
    }
    handle_print(msh, argv, i, is_with_newline);
    is_reading_flag = false;
    i++;
  }
  if (is_with_newline) {
    if (write(STDOUT_FILENO, "\n", 1) == ERROR)
      handle_exit(msh, EXIT_FAILURE, true);
  }
  handle_exit(msh, EXIT_SUCCESS, true);
}
