/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:32 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/14 01:48:55 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_home_path(char **res_path, char *path, t_var_node *env_vars)
{
	char	*home_path;

	if ((*res_path))
	{
		free((*res_path));
		(*res_path) = NULL;
	}
	home_path = get_env_var(env_vars, "HOME");
	if (is_emptystr(path))
	{
		(*res_path) = home_path;
		return ;
	}
	if (!home_path)
		return ;
	if (!path)
		(*res_path) = ft_strjoin(home_path, "");
	else
		(*res_path) = ft_strjoin(home_path, (path + 1));
}

static bool	is_dir_valid(char *path)
{
	if (!path)
		return (true);
	if (!ft_strncmp(path, "~", 1) || is_emptystr(path))
		return (true);
	if (!access(path, F_OK | R_OK))
		return (true);
	return (false);
}

static bool	validate_dir(char *path, t_msh **msh)
{
	if (!is_dir_valid(path) && access(path, F_OK))
		return (handle_err(msh, (t_err){T_BAD_REQUEST_ERR, path,
				NO_FILE_OR_DIR_MSG}, false), false);
	else if (!is_dir_valid(path) && access(path, R_OK))
		return (handle_err(msh, (t_err){T_BAD_REQUEST_ERR_PERM,
				path, NO_FILE_OR_DIR_MSG}, false), false);
	return (true);
}

void	cd(char *path, t_msh **msh)
{
	char	*res_path;
	char	*curr_path;

	res_path = NULL;
	curr_path = getcwd(NULL, 0);
	if (!validate_dir(path, msh))
		return ;
	if (path)
	{
		res_path = ft_strdup(path);
		if (!res_path)
			return ((void)handle_err(msh, (t_err){T_SYS_ERR, MALLOC}, false));
	}
	if (!path || is_emptystr(path) || !ft_strncmp(path, "~", 1))
		handle_home_path(&res_path, path, (*msh)->env_vars);
	update_var((*msh)->env_vars, "OLDPWD", curr_path);
	if (chdir(res_path))
		return ((void)handle_err(msh, (t_err){T_SYS_ERR, CD}, false));
	free(curr_path);
	curr_path = getcwd(NULL, 0);
	update_var((*msh)->env_vars, "PWD", curr_path);
	if (res_path)
		free(res_path);
	free(curr_path);
	(*msh)->exit_code = 0;
}
