/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:45:25 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/12 10:45:26 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exit(int is_on_failure)
{
	if (is_on_failure)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
