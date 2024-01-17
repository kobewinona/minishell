/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:27:53 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/17 12:27:55 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup3(int new_fd, int old_fd)
{
	int	res;

	res = dup2(new_fd, old_fd);
	if (res == ERROR)
		handle_exit(EXIT_SUCCESS);
	return (res);
}
