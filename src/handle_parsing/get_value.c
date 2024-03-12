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

char	*get_value(t_msh **msh, char **s)
{
	int		s_len;
	bool	is_in_quotes;
	char	end_char;
	char	*value;
	int		i;

	if (!(*s) || is_emptystr(*s))
		return (NULL);
	while ((*s) && ft_isspace((**s)))
		(*s)++;
	s_len = ft_strlen((*s));
	end_char = T_SPACE;
	is_in_quotes = false;
	value = (*s);
	i = 0;
	while ((*s)[i])
	{
		if (!is_in_quotes)
		{
			is_in_quotes = (*s)[i] == T_DOUBLE_QUOTE || (*s)[i] == T_SINGLE_QUOTE;
			if (is_in_quotes)
			{
				end_char = (*s)[i];
				ft_memmove(&(*s)[i], &(*s)[i + 1], s_len - i);
				s_len--;
				continue ;
			}
		}
		if (is_in_quotes && (*s)[i] == end_char)
		{
			ft_memmove(&(*s)[i], &(*s)[i + 1], s_len - i);
			s_len--;
			if (is_in_quotes)
			{
				is_in_quotes = false;
				end_char = T_SPACE;
			}
			continue ;
		}
		if ((*s)[i] == end_char)
			break ;
		i++;
	}
	if (is_in_quotes)
		return (handle_err(msh, (t_err){T_OTHER_ERR,
				UNEXPECTED_TOK_MSG, tokstr(end_char)}, false), NULL);
	if ((*s)[i])
		(*s)[i++] = '\0';
	(*s) += i;
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
// 					UNEXPECTED_EOF_MSG, tokstr(end_char)}, false), ERROR);
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
// 		return (handle_err(msh, (t_err){T_SYS_ERR, MALLOC}, false), NULL);
// 	while (*s && ft_isspace((**s)))
// 		(*s)++;
// 	if (extract_value(msh, &value, s) == ERROR)
// 	{
// 		free(value);
// 		return (NULL);
// 	}
// 	return (value);
// }
