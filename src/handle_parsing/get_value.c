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

static ssize_t	subtract_new_value(t_msh **msh,
	char **value, char **s, char end_char)
{
	ssize_t	val_len;

	val_len = 0;
	while ((*s)[val_len] && (*s)[val_len] != end_char)
	{
		if ((*s)[val_len] == T_VAR_EXP)
		{
			if (end_char == T_DOUBLE_QUOTE || end_char == T_SPACE)
			{
				if (join_values(msh, value, (*s), val_len) == ERROR)
					return (ERROR);
				(*s) += val_len;
				val_len = exp_env_var(msh, value, (*s), end_char);
				(*s) += val_len;
				val_len = 0;
				continue ;
			}
		}
		val_len++;
	}
	if (end_char != T_SPACE && (*s)[val_len] != end_char)
		return (ERROR);
	if (join_values(msh, value, (*s), val_len) == ERROR)
		return (ERROR);
	return (val_len);
}

// TODO add check inside quotes handling
static int	extract_value(t_msh **msh, char **value, char **s)
{
	char	end_char;
	ssize_t	val_len;
	bool	is_in_quotes;

	end_char = T_SPACE;
	val_len = 0;
	while ((*s)[val_len] && (*s)[val_len] != end_char)
	{
		is_in_quotes = (*s)[val_len] == T_DOUBLE_QUOTE || (*s)[val_len] == T_SINGLE_QUOTE;
		if (is_in_quotes)
		{
			if (val_len > 0)
			{
				if (join_values(msh, value, (*s), val_len) == ERROR)
					return (ERROR);
				(*s) += val_len;
				val_len = 0;
			}
			end_char = *(*s)++;
			while ((*s)[val_len] && (*s)[val_len] != end_char)
				val_len++;
			if ((*s)[val_len] != end_char)
				return (handle_err(msh, (t_err){T_OTHER_ERR, UNEXPECTED_EOF_MSG, tokstr(end_char)}, false).t_int);
			if (val_len > 0)
			{
				if (join_values(msh, value, (*s), val_len) == ERROR)
					return (ERROR);
			}
			(*s) += val_len + is_in_quotes;
			val_len = 0;
			end_char = T_SPACE;
			continue ;
		}
		if ((*s)[val_len] == T_VAR_EXP && end_char != T_SINGLE_QUOTE)
		{
			if (val_len > 0)
			{
				if (join_values(msh, value, (*s), val_len) == ERROR)
					return (ERROR);
				(*s) += val_len;
				val_len = 0;
			}
			val_len += exp_env_var(msh, value, (*s), end_char);
			(*s) += val_len;
			val_len = 0;
			continue ;
		}
		val_len++;
	}
	if (val_len > 0)
	{
		if (join_values(msh, value, (*s), val_len) == ERROR)
			return (ERROR);
		(*s) += val_len;
	}
	return (SUCCESS);
}

char	*get_value(t_msh **msh, char **s)
{
	char	*value;

	if (!(*s) || is_emptystr((*s)))
		return (NULL);
	value = NULL;
	value = ft_strdup("");
	if (!value)
		return (handle_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_null);
	while (*s && ft_isspace((**s)))
		(*s)++;
	if (extract_value(msh, &value, s) == ERROR)
	{
		free(value);
		return (NULL);
	}
	return (value);
}

// static ssize_t	subtract_new_value(t_msh **msh,
// 		char **value, char **s, char end_char)
// {
// 	ssize_t	val_len;

// 	val_len = 0;
// 	while ((*s)[val_len] && (*s)[val_len] != end_char)
// 	{
// 		if ((*s)[val_len] == T_VAR_EXP)
// 		{
// 			if (end_char == T_DOUBLE_QUOTE || end_char == T_SPACE)
// 			{
// 				if (join_values(msh, value, (*s), val_len) == ERROR)
// 					return (ERROR);
// 				(*s) += val_len;
// 				val_len = exp_env_var(msh, value, (*s), end_char);
// 				(*s) += val_len;
// 				val_len = 0;
// 				continue ;
// 			}
// 		}
// 		val_len++;
// 	}
// 	if (end_char != T_SPACE && (*s)[val_len] != end_char)
// 		return (ERROR);
// 	if (join_values(msh, value, (*s), val_len) == ERROR)
// 		return (ERROR);
// 	return (val_len);
// }

// static int	extract_value(t_msh **msh, char **value, char **s)
// {
// 	char	end_char;
// 	ssize_t	val_len;
// 	bool	is_in_quotes;

// 	while ((**s) && !ft_isspace((**s)))
// 	{
// 		end_char = T_SPACE;
// 		is_in_quotes = (**s) == T_DOUBLE_QUOTE || (**s) == T_SINGLE_QUOTE;
// 		if (is_in_quotes)
// 			end_char = *(*s)++;
// 		val_len = subtract_new_value(msh, value, s, end_char);
// 		if (val_len == ERROR)
// 			return (handle_err(msh, (t_err){T_OTHER_ERR,
// 					UNEXPECTED_EOF_MSG, tokstr(end_char)}, false).t_int);
// 		(*s) += val_len + is_in_quotes;
// 	}
// 	return (SUCCESS);
// }

// char	*get_value(t_msh **msh, char **s)
// {
// 	char	*value;

// 	if (!(*s) || is_emptystr((*s)))
// 		return (NULL);
// 	value = NULL;
// 	value = ft_strdup("");
// 	if (!value)
// 		return (handle_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_null);
// 	while (*s && ft_isspace((**s)))
// 		(*s)++;
// 	if (extract_value(msh, &value, s) == ERROR)
// 	{
// 		free(value);
// 		return (NULL);
// 	}
// 	return (value);
// }
