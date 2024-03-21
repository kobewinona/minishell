/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:40:32 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 11:35:28 by dklimkin         ###   ########.fr       */
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

static bool	is_dir_valid(char *path, t_msh **msh)
{
	bool	is_dir_valid;

	is_dir_valid = false;
	if (!path)
		is_dir_valid = true;
	else if (!ft_strncmp(path, "~", 1) || is_emptystr(path))
		is_dir_valid = true;
	else if (!access(path, F_OK | R_OK))
		is_dir_valid = true;
	if (!is_dir_valid && access(path, F_OK))
		return (handle_err(msh, CD_NO_FILE_OR_DIR, path, 1), false);
	else if (!is_dir_valid && access(path, R_OK))
		return (handle_err(msh, CD_PERM_DENIED, path, 1), false);
	return (is_dir_valid);
}

void	cd(char *path, t_msh **msh)
{
	char	*res_path;
	char	*curr_path;

	res_path = NULL;
	curr_path = getcwd(NULL, 0);
	if (!is_dir_valid(path, msh))
		return ;
	if (path)
	{
		res_path = ft_strdup(path);
		if (!res_path)
			return (handle_err(msh, SYSTEM, MALLOC, 1));
	}
	if (!path || is_emptystr(path) || !ft_strncmp(path, "~", 1))
		handle_home_path(&res_path, path, (*msh)->env_vars);
	update_var((*msh)->env_vars, "OLDPWD", curr_path);
	if (chdir(res_path))
		return (handle_err(msh, SYSTEM, CD, 1));
	free(curr_path);
	curr_path = getcwd(NULL, 0);
	update_var((*msh)->env_vars, "PWD", curr_path);
	if (res_path)
		free(res_path);
	free(curr_path);
	handle_exit(msh, EXIT_SUCCESS, true);
}
