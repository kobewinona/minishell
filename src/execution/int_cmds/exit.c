/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:06 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/14 14:03:07 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need to return exit code passed as arg / ext code of last executed cmdq
void	exit_cmd(char **argv, t_msh **msh)
{
	// if (argv[1] != NULL)
	// process_err(ERROR, (t_err){T_SYS_ERR, EXIT}, true);
	printf("exit\n");
	exit(SUCCESS);
}