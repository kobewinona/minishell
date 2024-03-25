/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:30:32 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/25 13:34:56 by dklimkin         ###   ########.fr       */
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
		if (varname[i] == '+' && varname[i + 1])
		{
			if (varname[i + 1] != '=')
				return (false);
			i++;
		}
		if (varname[i] == '=')
			break ;
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
		if (!ft_strncmp(varname, curr->name, 5000) && !curr->is_deleted)
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
		if (!curr->is_deleted && !curr->value)
			printf("declare -x %s\n", curr->name);
		else if (!curr->is_deleted)
			printf("declare -x %s=\"%s\"\n", curr->name, curr->value);
		curr = curr->next;
	}
}

static int	process_env_var(t_evar *evar, char *s)
{
	char	*append;
	char	*sep;
	int		value_index;

	value_index = 0;
	sep = ft_strchr(s, '=');
	if (sep)
	{
		(*sep) = '\0';
		value_index++;
		evar->name = s;
	}
	else
		evar->name = s;
	append = ft_strchr(evar->name, '+');
	evar->is_to_append = append != NULL && !(*(append + 1));
	if (evar->is_to_append)
		(*append) = '\0';
	value_index += evar->is_to_append;
	s += value_index + ft_strlen(evar->name);
	if (!sep && (!evar->value || is_emptystr(evar->value)))
		evar->value = NULL;
	else
		evar->value = s;
	return (SUCCESS);
}

void	export(char **argv, t_msh **msh)
{
	t_evar	evar;
	int		i;

	if (!argv[1])
		return (print_declared_vars((*msh)->env_vars));
	ft_memset(&evar, 0, sizeof(t_evar));
	i = 1;
	while (argv[i])
	{
		if (!is_valid_varname(argv[i]))
		{
			handle_err(msh, EXPORT_INVALID_ID, argv[i], 1);
			i++;
			continue ;
		}
		if (process_env_var(&evar, argv[i]) == ERROR)
			return ;
		update_var((*msh)->env_vars, evar);
		ft_memset(&evar, 0, sizeof(t_evar));
		i++;
	}
	handle_exit(msh, (*msh)->exit_code, true);
}
