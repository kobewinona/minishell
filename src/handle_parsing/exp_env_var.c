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

static int	handle_spec_var(t_msh **msh, char **value, const char *s)
{
	char	*var_value;
	bool	is_spec_var_included;
	int		join_res;

	var_value = NULL;
	is_spec_var_included = false;
	if ((*s) == '0')
		var_value = (*msh)->script_name;
	if ((*s) == T_QUESTION_MARK)
		var_value = ft_itoa((*msh)->exit_code);
	if (var_value)
	{
		is_spec_var_included = true;
		join_res = join_values(msh, value, var_value, ft_strlen(var_value));
		if ((*s) != '0')
			free(var_value);
		if (join_res == ERROR)
			return (ERROR);
	}
	return (is_spec_var_included);
}

static ssize_t	update_val(t_msh **msh, char **value, char *s, ssize_t len)
{
	char	*var_key;
	char	*var_value;

	if (len <= 1)
	{
		if (join_values(msh, value, "$", 1) == ERROR)
			return (ERROR);
		return (len);
	}
	var_key = ft_substr(s, 0, len);
	if (!var_key)
		return (print_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_int);
	var_value = get_env_var((*msh)->env_vars, var_key);
	free(var_key);
	if (var_value)
	{
		if (join_values(msh, value, var_value, ft_strlen(var_value)) == ERROR)
			return (ERROR);
	}
	return (len);
}

ssize_t	exp_env_var(t_msh **msh, char **value, char *s, char end_char)
{
	ssize_t	var_len;
	bool	is_tok_included;

	var_len = 0;
	is_tok_included = false;
	if (s[var_len] == T_VAR_EXP)
		is_tok_included = true;
	var_len += is_tok_included;
	if (is_tok_included && handle_spec_var(msh, value, &s[var_len]))
		return (var_len + 1);
	while (s[var_len] && (!ft_isspace(s[var_len]) || s[var_len] == end_char)
		&& (ft_isalpha(s[var_len]) || s[var_len] == T_UNDERSCORE))
		var_len++;
	var_len = update_val(msh, value,
			(s + is_tok_included), (var_len - is_tok_included));
	if (var_len == ERROR)
		return (ERROR);
	return (var_len + is_tok_included);
}
