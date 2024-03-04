/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:11:11 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/04 17:28:51 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_env_var(t_msh **msh, char **value, char *s, char end_char)
{
	char	*var_key;
	char	*var_value;
	int		var_len;
	bool	is_tok_included;

	var_len = 0;
	is_tok_included = false;
	if (s[var_len] == T_VAR_EXP)
		is_tok_included = true;
	var_len += is_tok_included;
	while (s[var_len] && (!ft_isspace(s[var_len]) || s[var_len] == end_char)
		&& (ft_isalpha(s[var_len]) || s[var_len] == T_UNDERSCORE))
		var_len++;
	var_key = ft_substr(s, is_tok_included, (var_len - is_tok_included));
	if (!var_key)
		return (print_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_int);
	var_value = get_env_var((*msh)->env_vars, var_key);
	if (var_value)
		join_values(msh, value, var_value, (int) ft_strlen(var_value));
	return (var_len);
}
