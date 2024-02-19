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

static void	handle_home_path(char **res_path, char *path, t_var_node *env_vars)
{
	char	*home_path;

	if (res_path && (*res_path))
	{
		free((*res_path));
		(*res_path) = NULL;
	}
	home_path = get_env_var(env_vars, "HOME");
	if (!home_path)
	{
		handle_err(ERROR, (t_err){T_SYS_ERR, CD, GETENV}, false);
		return ;
	}
	if (!path)
		(*res_path) = ft_strjoin(home_path, "");
	else
		(*res_path) = ft_strjoin(home_path, (path + 1));
}

void	cd(char *path, t_var_node *env_vars)
{
	char	*res_path;
	int		ret;

	res_path = NULL;
	if (path)
		res_path = ft_strdup(path);
	if (!path || !ft_strncmp(path, "~", 1))
		handle_home_path(&res_path, path, env_vars);
	
	update_var(env_vars, "OLDPWD", get_env_var(env_vars, "PWD"));
	ret = chdir(res_path);
	update_var(env_vars, "PWD", res_path); //update our pwd
	if (res_path)
		free(res_path);
	if (ret == ERROR)
		handle_err(ERROR, (t_err){T_SYS_ERR, CD, path}, false);
}
