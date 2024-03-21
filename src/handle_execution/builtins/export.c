/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:30:32 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/21 03:59:34 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_varname(const char *varname)
{
	int	i;

	if (!(ft_isalpha(varname[0]) || varname[0] == '_'))
		return (false);
	i = 0;
	while (varname[i])
	{
		if (!ft_isalnum(varname[i]) && !(varname[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

bool	is_var_deleted(t_var_node *env_vars, char *varname)
{
	t_var_node	*curr;

	curr = env_vars;
	while (curr)
	{
		if (!ft_strncmp(varname, curr->name, 5000) && !curr->deleted)
			return (false);
		curr = curr->next;
	}
	return (true);
}

static void	print_declared_vars(t_var_node *env_vars)
{
	t_var_node	*curr;

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
	char	*var_name;
	int		i;

	if (argv[1] == NULL)
		return (print_declared_vars((*msh)->env_vars));
	i = 1;
	while (argv[i])
	{
		var_name = ft_strtok(argv[i], "=");
		if (!is_valid_varname(var_name))
			return (handle_err(msh, EXPORT_INVALID_ARG, var_name, 1));
		update_var((*msh)->env_vars, var_name, ft_strtok(NULL, "="));
		i++;
	}
	handle_exit(msh, EXIT_SUCCESS);
}
