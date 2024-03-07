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
		{
			printf("declare -x %s=\"%s\"\n", curr->name, curr->value);
		}
		else if (!curr->deleted && !curr->value_assigned)
		{
			printf("declare -x %s\n", curr->name);
		}
		curr = curr->next;
	}
}

void	export(char **argv, t_msh **msh)
{
	char	**keyval_arr;
	int		i;

	if (argv[1] == NULL)
		return (print_declared_vars((*msh)->env_vars));
	i = 1;
	while (argv[i])
	{
		if (!is_valid_varname(argv[i]))
		{
			print_err(msh, (t_err){1, EXPORT_INVALID_ARG_MSH1, argv[i]}, false);
			return ;
		}
		if (is_char_there(argv[i], '='))
		{
			keyval_arr = ft_split(argv[i], '=');
			if (keyval_arr == NULL || !is_valid_varname(keyval_arr[0]))
				return (free_array(keyval_arr));
			update_var((*msh)->env_vars, keyval_arr[0], keyval_arr[1]);
		}
		else if (is_valid_varname(argv[i]))
			update_var((*msh)->env_vars, argv[i], NULL);
		i++;
	}
	(*msh)->exit_code = 0;
}
