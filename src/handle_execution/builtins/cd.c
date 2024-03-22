/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:32 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/22 01:44:37 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(t_msh **msh, char *path, bool is_strict_home_path)
{
	char	*home_path;
	char	*res_path;

	res_path = NULL;
	home_path = get_env_var((*msh)->env_vars, "HOME");
	if (!home_path)
		return (NULL);
	if (is_strict_home_path)
	{
		res_path = ft_strdup(home_path);
		if (!res_path)
			return (handle_err(msh, SYSTEM, MALLOC, 1), NULL);
	}
	if (path[1] == '/')
	{
		res_path = ft_strjoin(home_path, (path + 1));
		if (!res_path)
			return (handle_err(msh, SYSTEM, MALLOC, 1), NULL);
	}
	return (res_path);
}

static char	*get_back_path(t_msh **msh)
{
	char	*back_path;
	char	*res_path;

	back_path = get_env_var((*msh)->env_vars, "OLDPWD");
	res_path = ft_strdup(back_path);
	if (!res_path)
		return (handle_err(msh, SYSTEM, MALLOC, 1), NULL);
	return (res_path);
}

static bool	is_path_valid(char *path, t_msh **msh)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, R_OK) == 0)
			return (true);
		else
			return (handle_err(msh, CD_PERM_DENIED, path, 1), false);
	}
	return (handle_err(msh, CD_NO_FILE_OR_DIR, path, 1), false);
}

static char	*process_path(t_msh **msh, char *path)
{
	char	*res_path;
	size_t	path_len;

	if (!path || is_emptystr(path))
		return (get_home_path(msh, path, true));
	path_len = ft_strlen(path);
	if (!ft_strncmp(path, "-", path_len))
		return (get_back_path(msh));
	if (path[0] == '-' && ft_strncmp(path, "--", path_len))
	{
		path[2] = '\0';
		return (handle_err(msh, CD_INVALID_OPTION, path, 1), NULL);
	}
	if (!ft_strncmp(path, "--", path_len))
		return (get_home_path(msh, path, true));
	if (path[0] == '~')
		return (get_home_path(msh, path, path[1] == '\0'));
	res_path = ft_strdup(path);
	if (!res_path)
		return (handle_err(msh, SYSTEM, MALLOC, 1), NULL);
	return (res_path);
}

void	cd(char *path, t_msh **msh)
{
	char	*res_path;
	char	*curr_path;
	char	*deleted_path;

	curr_path = getcwd(NULL, 0);
	res_path = process_path(msh, path);
	if (!res_path)
		res_path = path;
	if (!is_path_valid(res_path, msh))
		return ;
	if (curr_path && !is_emptystr(curr_path))
		update_var((*msh)->env_vars, "OLDPWD", curr_path);
	else
	{
		deleted_path = get_env_var((*msh)->env_vars, "PWD");
		update_var((*msh)->env_vars, "OLDPWD", deleted_path);
	}
	if (chdir(res_path))
		return (handle_err(msh, SYSTEM, CD, 1));
	free(curr_path);
	curr_path = getcwd(NULL, 0);
	update_var((*msh)->env_vars, "PWD", curr_path);
	free(res_path);
	free(curr_path);
	handle_exit(msh, EXIT_SUCCESS, true);
}
