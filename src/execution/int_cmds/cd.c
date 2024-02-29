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

	if ((*res_path))
	{
		free((*res_path));
		(*res_path) = NULL;
	}
	home_path = get_env_var(env_vars, "HOME");
	if (!home_path)
	{
//		handle_err(ERROR, (t_err){T_SYS_ERR, CD, GETENV}, false);
		return ;
	}
	if (!path)
		(*res_path) = ft_strjoin(home_path, "");
	else
		(*res_path) = ft_strjoin(home_path, (path + 1));
}

static bool is_dir_valid(char *path, t_msh **msh)
{
	if (!access(path, F_OK | R_OK))
		return (true);
	return (false);
}

void	cd(char *path, t_msh **msh)
{
	char	*res_path;
	int		ret;
	char	*curr_path;

	
	if (!is_dir_valid(path, msh))
	{
		(*msh)->exit_code = T_EXEC;
		printf("%s: %s: %s\n", PRG_NAME, path, "no such file or directory");
		return ;
	}
	res_path = NULL;
	curr_path = getcwd(NULL, 0);
	if (path)
		res_path = ft_strdup(path);
	if (!path || !ft_strncmp(path, "~", 1))
		handle_home_path(&res_path, path, (*msh)->env_vars);
	update_var((*msh)->env_vars, "OLDPWD", curr_path);
	free(curr_path);

	ret = chdir(res_path);
	curr_path =  getcwd(NULL, 0);
	update_var((*msh)->env_vars, "PWD", curr_path);
	if (res_path)
		free(res_path);
	free(curr_path);
	(*msh)->exit_code = ret;
}
