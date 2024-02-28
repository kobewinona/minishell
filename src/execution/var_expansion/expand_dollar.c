/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:04:50 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/12 18:04:51 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// implement the same but for local checks
bool	is_wrapped_single_quotes(char **argv)
{
	char	first_c;
	char	last_c;
	int		i;
	int		j;

	first_c = argv[1][0];
	i = 1;
	j = 0;
	while (argv[i] != NULL)
		i++;
	i--;
	while (argv[i][j])
		j++;
	j--;
	last_c = argv[i][j];
	printf("first = %c;last=%c\n", first_c, last_c);
	if (first_c == last_c && last_c == '\'')
		return (false);
	return (true);
}

// make it add double quote at the end as it should
void	expand_dollar(char **arg, t_var_node *env_vars, t_msh **msh)
{
	char	**split_arr;
	char	*expanded_str;
	char	*value;
	int		i;

	split_arr = ft_split(*arg, '$');
	expanded_str = NULL;
	i = 0;
	if (**arg != '$')
	{
		expanded_str = split_arr[0];
		i++;
	}
	while (split_arr[i])
	{
		if (split_arr[i][0] == '?')
			value = ft_itoa((*msh)->exit_code);
		else

			value = get_env_var(env_vars, ft_strtrim(split_arr[i], "\""));
		
		if (value && expanded_str)
			expanded_str = ft_strjoin(expanded_str, value);
		else if (value && expanded_str == NULL)
			expanded_str = ft_strdup(value);
		i++;
	}
	*arg = expanded_str;
	free_array(split_arr);
}

void	replace_dollar_sign(char **argv, t_var_node *env_vars, t_msh **msh)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_char_there(argv[i], '$'))
			expand_dollar(&argv[i], env_vars, msh);
		i++;
	}
}
