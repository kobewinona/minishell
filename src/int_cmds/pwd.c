/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:45:46 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/16 21:45:46 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **argv)
{
	char	*curr_dir;
	size_t	size;

	(void)argv;
	curr_dir = NULL;
	size = 0;
	curr_dir = getcwd(curr_dir, size);
	if (!curr_dir)
		handle_exit(EXIT_FAILURE);
	ft_putstr_fd(curr_dir, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(curr_dir);
	handle_exit(EXIT_SUCCESS);
}
