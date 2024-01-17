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

	home_path = getenv("HOME");
	if (!home_path)
		handle_error(ERROR, CD, NULL, false);
	return (home_path);
}

void	cd(char *path)
{
	char	*res_path;
	int		ret;

	res_path = NULL;
	res_path = ft_strdup(path);
	if (!res_path)
		handle_error(ERROR, CD, NULL, false);
	if (!path || !ft_strncmp(path, "~", 1))
	{
		free(res_path);
		res_path = NULL;
		res_path = ft_strjoin(get_home_path(), (path + 1));
	}
	ret = chdir(res_path);
	free(res_path);
	if (ret == ERROR)
		handle_error(ERROR, CD, path, false);
}
