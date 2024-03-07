/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:30:32 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/16 12:30:33 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_varname(const char *varname)
{
	return (ft_isalpha(*varname) || *varname == '_');
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
			return ((void) handle_err(msh, (t_err){T_BAD_REQUEST_ERR,
					EXPORT, var_name}, false));
		update_var((*msh)->env_vars, var_name, ft_strtok(NULL, "="));
		i++;
	}
	(*msh)->exit_code = 0;
}
