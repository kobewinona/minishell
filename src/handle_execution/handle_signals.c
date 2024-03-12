/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:24:51 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/04 12:24:53 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	interrupt_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	// printf("this pid %d handling it...", getpid());
	write(1, "\n", 1);
	if (signum == SIGINT && info->si_pid)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	track_signals(t_msh **msh)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &interrupt_handler;
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

static void	idle_interrupt_handler(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
}

int	ignore_signals(t_msh **msh)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &idle_interrupt_handler;
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
