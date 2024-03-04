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

static int	get_val(t_msh **msh, char **value, char *s, char end_char)
{
	int		val_len;
	char	*temp1;
	char	*temp2;

	val_len = 0;
	while (s[val_len] && s[val_len] != end_char)
	{
		if (s[val_len] == T_VAR_EXP && end_char == T_DOUBLE_QUOTE)
			expand_var(msh, &s[val_len]);
		val_len++;
	}
	if (end_char != T_SPACE && s[val_len] != end_char)
		return (ERROR);
	else
	{
		temp1 = ft_substr(s, 0, val_len);
		temp2 = ft_strjoin((*value), temp1);
		free(*value);
		(*value) = temp2;
		free(temp1);
	}
	return (val_len);
}

static int	populate_value(t_msh **msh, char **value, char **s)
{
	char	end_char;
	int		val_len;
	bool	is_in_quotes;

	while (*s && ft_isspace((**s)))
		(*s)++;
	while ((**s) && !ft_isspace((**s)))
	{
		end_char = T_SPACE;
		is_in_quotes = (**s) == T_DOUBLE_QUOTE || (**s) == T_SINGLE_QUOTE;
		if (is_in_quotes)
			end_char = *(*s)++;
		val_len = get_val(msh, value, (*s), end_char);
		if (val_len == ERROR)
		{
			log_err(msh, T_SYNTAX_ERR, UNEXPECTED_EOF_MSG, tokstr(end_char));
			return (ERROR);
		}
		(*s) += val_len + is_in_quotes;
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
	{
		log_err(msh, T_SYS_ERR, MALLOC, NULL);
		return (NULL);
	}
	if (populate_value(msh, &value, s) == ERROR)
		return (NULL);
//	if (is_emptystr(value))
//	{
//		free(value);
//		return (NULL);
//	}
	return (value);
}

//static void	move_chars(char *s)
//{
//	int	write;
//	int	read;
//
//	write = 0;
//	read = write + 1;
//	while (s[read])
//		s[write++] = s[read++];
//	s[write] = '\0';
//}
//
//static int	nullterminate(t_msh **msh, char **s, char end_char)
//{
//	int		i;
//
//	i = 0;
//	while ((*s)[i] && (*s)[i] != end_char)
//	{
//		if ((*s)[i] == T_VAR_EXP && end_char == T_DOUBLE_QUOTE)
//			expand_var(msh, &(*s)[i]);
//		i++;
//	}
//	if (end_char != T_SPACE && (*s)[i] != end_char)
//		return (ERROR);
//	else
//	{
//		while ((*s)[i] && !ft_isspace((*s)[i]))
//		{
//			move_chars(&((*s)[i]));
//			while ((*s)[i] && !ft_isspace((*s)[i]) && (*s)[i] != end_char)
//				i++;
//		}
//		if (ft_isspace((*s)[i]))
//			(*s)[i++] = '\0';
//		(*s) += i;
//	}
//	return (SUCCESS);
//}
//
//static char	*prepare_value(t_msh **msh, char **s)
//{
//	char	*value;
//	char	end_char;
//	bool	is_in_quotes;
//
//	while (*s && ft_isspace((**s)))
//		(*s)++;
//	while ((**s) && !ft_isspace((**s)))
//	{
//		end_char = T_SPACE;
//		is_in_quotes = (**s) == T_DOUBLE_QUOTE || (**s) == T_SINGLE_QUOTE;
//		if (is_in_quotes)
//			end_char = *(*s)++;
//		value = (*s);
//		if (nullterminate(msh, s, end_char) == ERROR)
//			return (NULL);
//		return (value);
//	}
//	return ((*s));
//}
//
//char	*get_value(t_msh **msh, char **s)
//{
//	char	*value;
//
//	if (!(*s) || is_emptystr((*s)))
//		return (NULL);
//	value = prepare_value(msh, s);
//	if (is_emptystr(value))
//		return (NULL);
//	return (value);
//}
