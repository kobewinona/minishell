/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:30:32 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/23 15:53:30 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_varname(const char *varname)
{
	int	i;

	if (!varname)
		return (false);
	if (!(ft_isalpha(varname[0]) || varname[0] == '_'))
		return (false);
	i = 0;
	while (varname[i])
	{
		if (!ft_isalnum(varname[i]) && varname[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	is_var_deleted(t_env *env_vars, char *varname)
{
	t_env	*curr;

	curr = env_vars;
	while (curr)
	{
		if (!ft_strncmp(varname, curr->name, 5000) && !curr->deleted)
			return (false);
		curr = curr->next;
	}
	return (true);
}

static void	print_declared_vars(t_env *env_vars)
{
	t_env	*curr;

	curr = env_vars;
	while (curr)
	{
		if (!curr->deleted && curr->value_assigned)
			printf("declare -x %s=\"%s\"\n", curr->name, curr->value);
		else if (!curr->deleted && !curr->value_assigned)
			printf("declare -x %s\n", curr->name);
		curr = curr->next;
	}
}

void	export(char **argv, t_msh **msh)
{
	char	*arg;
	char	*var_name;
	int		i;

	if (argv[1] == NULL)
		return (print_declared_vars((*msh)->env_vars));
	i = 1;
	while (argv[i])
	{
		arg = ft_strdup(argv[i]);
		var_name = ft_strtok(argv[i], "=");
		if (!var_name)
			handle_err(msh, EXPORT_INVALID_ID, "=", 1);
		if (!is_valid_varname(var_name))
		{
			handle_err(msh, EXPORT_INVALID_ID, arg, 1);
			i++;
			continue ;
		}
		update_var((*msh)->env_vars, arg, ft_strtok(NULL, "="));
		free(arg);
		i++;
	}
	handle_exit(msh, (*msh)->exit_code, true);
}
