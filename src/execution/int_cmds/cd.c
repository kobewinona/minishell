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

static void	handle_home_path(char **res_path, char *path)
{
	char	*home_path;

	if (res_path && (*res_path))
	{
		free((*res_path));
		(*res_path) = NULL;
	}
	home_path = getenv("HOME");
	if (!home_path)
	{
		handle_err(ERROR, CD, GETENV, false);
		return ;
	}
	if (!path)
		(*res_path) = ft_strjoin(home_path, "");
	else
		(*res_path) = ft_strjoin(home_path, (path + 1));
}

void	cd(char *path)
{
	char	*res_path;
	int		ret;

	res_path = NULL;
	if (path)
		res_path = ft_strdup(path);
	if (!path || !ft_strncmp(path, "~", 1))
		handle_home_path(&res_path, path);
	ret = chdir(res_path);
	if (res_path)
		free(res_path);
	if (ret == ERROR)
		handle_err(ERROR, CD, path, false);
}
