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

static bool	process_quotes(t_val *ctx, char *c, int i)
{
	if (!ctx->is_in_quotes)
	{
		(ctx->is_in_quotes) = (*c) == T_DOUBLE_QUOTE || (*c) == T_SINGLE_QUOTE;
		if (ctx->is_in_quotes)
		{
			ctx->end_char = (*c);
			return (ft_memmove(c, c + 1, ((ctx->s_len--) - i)) , true);
		}
	}
	if (ctx->is_in_quotes && (*c) == ctx->end_char)
	{
		if (ctx->is_in_quotes)
			(*ctx) = (t_val){ctx->s, ctx->s_len, false, T_SPACE};
		return (ft_memmove(c, c + 1, ((ctx->s_len--) - i)), true);
	}
	return (false);
}

static size_t	extract_value(t_val *ctx)
{
	size_t	len;
	size_t	i;

	len = ft_strlen((*ctx->s));
	i = 0;
	while ((*ctx->s)[i])
	{
		if (process_quotes(ctx, &(*ctx->s)[i], i))
			continue ;
		if ((*ctx->s)[i] == ctx->end_char)
			break ;
		i++;
	}
	return (i);
}

char	*get_value(t_msh **msh, char **s)
{
	t_val	ctx;
	char	*value;
	int		len;

	if (!(*s) || is_emptystr(*s))
		return (NULL);
	while ((*s) && ft_isspace((**s)))
		(*s)++;
	value = (*s);
	ctx = (t_val){s, ft_strlen((*s)), false, T_SPACE};
	len = extract_value(&ctx);
	if (ctx.is_in_quotes)
		return (handle_err(msh, (t_err){T_OTHER_ERR,
				UNEXPECTED_TOK_MSG, tokstr(ctx.end_char)}, false), NULL);
	if ((*s)[len])
		(*s)[len++] = '\0';
	(*s) += len;
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
