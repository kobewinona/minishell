/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:32 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/15 12:40:32 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **argv)
{
	char	*path;

	path = argv[1];
	if (!path)
		return ;
	else if (ft_strncmp(path, "/", 1) == 0)
		ft_putstr_fd("cd: /: No such file or directory\n", STDERR_FILENO);
	else if (ft_strncmp(path, "~", 1) == 0)
		ft_putstr_fd("cd: ~: No such file or directory\n", STDERR_FILENO);
	else if (ft_strncmp(path, "-", 1) == 0)
		ft_putstr_fd("cd: -: No such file or directory\n", STDERR_FILENO);
	else
	{
		if (chdir(path) != 0)
			perror(NULL);
	}
}
