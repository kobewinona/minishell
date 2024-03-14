/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:24:51 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/14 19:06:24 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_interrupt_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	write(STDOUT_FILENO, "\n", 1);
	if (signum == SIGINT && info->si_pid)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	handle_signals(t_msh **msh)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &handle_interrupt_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		return (handle_err(msh, (t_err){T_SYS_ERR, SIG}, false), ERROR);
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGTERM, &sa, NULL) == ERROR)
		return (handle_err(msh, (t_err){T_SYS_ERR, SIG}, false), ERROR);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
		return (handle_err(msh, (t_err){T_SYS_ERR, SIG}, false), ERROR);
	return (SUCCESS);
}
