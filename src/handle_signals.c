/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:24:51 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/25 18:10:57 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_interrupt(int signum) {
  (void)signum;
  if (write(STDOUT_FILENO, "\n", 1) == ERROR)
    return;
  if (g_state == IS_IDLE) {
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    return;
  }
  if (g_state == IS_IN_HEREDOC)
    close(STDIN_FILENO);
}

int setup_signal(int signum, void (*handler)(int)) {
  struct sigaction sa;

  ft_memset(&sa, 0, sizeof(sa));
  sigemptyset(&sa.sa_mask);
  sa.sa_handler = handler;
  return (sigaction(signum, &sa, NULL));
}

int init_signals(t_msh **msh) {
  if (setup_signal(SIGINT, handle_interrupt) == ERROR)
    return (handle_err(msh, SYSTEM, "SIGINT setup failed", 1), ERROR);
  if (setup_signal(SIGTERM, SIG_DFL) == ERROR)
    return (handle_err(msh, SYSTEM, "SIGTERM setup failed", 1), ERROR);
  if (setup_signal(SIGQUIT, SIG_IGN) == ERROR)
    return (handle_err(msh, SYSTEM, "SIGQUIT setup failed", 1), ERROR);
  return (SUCCESS);
}
