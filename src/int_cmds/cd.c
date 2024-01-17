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

static char	*get_home_path(void)
{
	char	*home_path;

	home_path = NULL;
	home_path = getenv("HOME");
	if (!home_path)
	{
		ft_putstr_fd(
			"cd: ~: The environment variable HOME is not set\n",
			STDERR_FILENO);
	}
	return (home_path);
}

void	cd(char *path)
{
	if (!path || ft_strncmp(path, "~", 1) == 0)
		chdir1(get_home_path());
	else if (ft_strncmp(path, "-", 1) == 0)
		return (ft_putstr_fd(
				"cd: -: No such file or directory\n",
				STDERR_FILENO));
	else
		chdir1(path);
}
