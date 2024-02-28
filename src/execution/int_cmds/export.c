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

//handle export without args (prints declared vars in ascii order)
//handle declaration without assignment

//export VAR=: empty string as value
//export VAR : declare var without assignment
//check for correctness of name

// Environment variable names used by the utilities in the Shell and Utilities volume of IEEE Std 1003.1-2001 consist
//  solely of uppercase letters, digits, and the '_' 
// (underscore) from the characters defined in Portable Character Set and do not begin with a digit. 
// Other characters may be permitted by an implementation; applications shall tolerate the presence of such names

static bool	is_valid_varname(char *varname)
{
	return (!ft_isdigit(*varname));
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
	{
		print_declared_vars((*msh)->env_vars);
		return ;

	}
	i = 1;
	while (argv[i])
	{
		if (!is_valid_varname(argv[i]))
			return ; //need to add some message
		if (is_char_there(argv[i], '='))
		{
			keyval_arr = ft_split(argv[i], '=');
			if (keyval_arr == NULL || !is_valid_varname(keyval_arr[0]))
			{
				free_array(keyval_arr);
				return ;
			}
			update_var((*msh)->env_vars, keyval_arr[0], keyval_arr[1]);
		}
		else
		{
			if (is_valid_varname(argv[i]) && is_var_deleted((*msh)->env_vars, argv[i]))
				update_var((*msh)->env_vars, argv[i], NULL);
		}
		i++;
	}

	(*msh)->exit_code = 0;

}
