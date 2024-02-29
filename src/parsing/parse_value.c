/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:06:00 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/29 19:06:01 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_var(t_msh **msh, const char *s)
{
	char	*expanded_var;

	return (expanded_var);
}

static int	get_val(t_msh **msh, char **value, char *s)
{
	char	end_char;
	int		val_len;
	bool	is_in_double_quotes;
	bool	is_in_single_quotes;
	char	*temp1;
	char	*temp2;

	is_in_double_quotes = *s == T_DOUBLE_QUOTE;
	is_in_single_quotes = *s == T_SINGLE_QUOTE;
	end_char = T_SPACE;
	if (is_in_double_quotes || is_in_single_quotes)
		end_char = *(s)++;
	val_len = 0;
	while (s[val_len] && s[val_len] != end_char)
	{
		if (s[val_len] == T_VAR_EXP && is_in_double_quotes)
			expand_var(msh, &s[val_len]);
		val_len++;
	}
	if (end_char != T_SPACE && s[val_len] != end_char)
	{
		log_err(msh, T_SYNTAX_ERR, UNEXPECTED_EOF_MSG, tokstr(end_char));
		return (ERROR);
	}
	else
	{
		temp1 = ft_substr(s, 0, val_len);
		temp2 = ft_strjoin((*value), temp1);
		free(*value);
		(*value) = temp2;
		free(temp1);
		val_len += is_in_double_quotes + is_in_single_quotes;
		val_len += is_in_double_quotes + is_in_single_quotes;
	}
	return (val_len);
}

static void	populate_value(t_msh **msh, char **value, char **s)
{
	int		val_len;

	while (*s && ft_isspace((**s)))
		(*s)++;
	while ((**s) && !ft_isspace((**s)))
	{
		val_len = get_val(msh, value, (*s));
		if (val_len == ERROR)
			return ;
		(*s) += val_len;
	}
}

char	*get_value(t_msh **msh, char **s)
{
	char	*value;

	if (!(*s) || is_emptystr((*s)))
		return (NULL);
	value = NULL;
	value = ft_strdup("");
	if (!value)
	{
		log_err(msh, T_SYS_ERR, MALLOC, NULL);
		return (NULL);
	}
	populate_value(msh, &value, s);
	if (is_emptystr(value))
	{
		free(value);
		return (NULL);
	}
	return (value);
}
