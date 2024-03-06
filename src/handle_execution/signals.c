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


//use info about state READ/RUNNING to
// redisplay promt correctly


void interupt_handler(int sig) 
{	
	g_signumber = 128 + sig;
	signal(SIGINT, interupt_handler);
    if (sig == SIGINT) 
	{
        write(1, "\n", 1);
		
		rl_on_new_line();
		rl_replace_line("", 0);
		return ;
    }
}

void track_signals(bool is_child) 
{
    struct sigaction sa;


    sigemptyset(&sa.sa_mask);
	sa.sa_handler = interupt_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);


	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);


}
