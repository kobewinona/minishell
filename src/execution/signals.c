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


void parent_handler(int sig, siginfo_t *info, void *context) 
{
	printf("sipid = %d\n", info->si_pid);
	printf("upid = %d\n", info->si_uid);

    if (sig == SIGINT) 
	{
        write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		//need to update $? here
		return ;
    }
	if (sig == SIGQUIT)
	{
		//free shell
		printf("Ctr + \\ does nothing \n");
		//need to update $? here
	}
	if (sig == SIGTERM)
	{
		printf("DEFAULT behavior\n");
		// need to exit with 128 + SIGTERM
		exit(EXIT_SUCCESS);
	}


}

void track_signals() {
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = parent_handler; // Set the handler
    sa.sa_flags = SA_SIGINFO;

    // Correctly use sigaction
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction failed");
    }

	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
