/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:24:51 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/20 22:23:42 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signals(int signum, siginfo_t *info, void *context)
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

int	init_signals_handle(t_msh **msh)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &handle_signals;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		return (handle_err(msh, (t_err){T_SYS_ERR, SIG, NULL}, false), ERROR);
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGTERM, &sa, NULL) == ERROR)
		return (handle_err(msh, (t_err){T_SYS_ERR, SIG, NULL}, false), ERROR);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
		return (handle_err(msh, (t_err){T_SYS_ERR, SIG, NULL}, false), ERROR);
	return (SUCCESS);
}
