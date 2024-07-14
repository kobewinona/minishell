/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:06 by sliashko          #+#    #+#             */
/*   Updated: 2024/04/04 16:47:24 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_valid_arg(char *s) {
  int i;

  i = (*s) == '+' || (*s) == '-';
  while (s[i]) {
    if (!ft_isdigit(s[i])) {
      if (ft_atoi(s) == 0)
        return (false);
    }
    i++;
  }
  return (true);
}

void exit_cmd(char **argv, t_msh **msh) {
  int exit_code;

  ft_putstr_fd("exit\n", STDOUT_FILENO);
  exit_code = EXIT_SUCCESS;
  if (argv[1]) {
    if (!ft_strncmp(argv[1], "--", 2))
      handle_exit(msh, exit_code, false);
    if (!is_valid_arg(argv[1])) {
      handle_err(msh, EXIT_INVALID_ARG, argv[1], 2);
      handle_exit(msh, 2, false);
    }
    if (argv[2])
      return (handle_err(msh, TOO_MANY_ARGS, EXIT, 1));
    exit_code = ft_atoi(argv[1]);
  }
  handle_exit(msh, exit_code, false);
}
