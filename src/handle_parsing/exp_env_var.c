/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:15:21 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/19 11:12:33 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int validate_env_var(t_msh * *msh, const char *s, char *end_char)
// {
// 	int		i;

// 	i = (*s) == T_VAR_EXP;
// 	if (s[i] == T_CURLY_OPEN || s[i] == T_SQUARE_OPEN || s[i] == T_BRACKET_OPEN)
// 	{
// 		(*end_char) = (s[i] + 2) - (s[i] == T_BRACKET_OPEN);
// 		i++;
// 	}
// 	if (s[i])
// 	{
// 		if ((*end_char) == T_CURLY_CLOSE && !ft_isalpha(s[i]) && s[i++] != '_')
// 			return (handle_err(msh, (t_err){T_BAD_REQUEST_ERR,
// 					(char *)s, BAD_SUBST_MSG}, false), ERROR);
// 	}
// 	while (s[i] && s[i] != (*end_char))
// 		i++;
// 	if ((*end_char) != T_SPACE && s[i] != (*end_char))
// 	{
// 		handle_err(msh, (t_err){T_OTHER_ERR,
// 			UNEXPECTED_EOF_TOK_MSG, tokstr((*end_char))}, false);
// 		return (handle_err(msh, (t_err){T_OTHER_ERR,
// 				SYNTAX_ERR_MSG, UNEXPECTED_EOF_MSH}, false), ERROR);
// 	}
// 	return (!((*end_char) != T_SPACE && s[i] != (*end_char)));
// }

// static size_t update_input(t_msh **msh, t_ctx *ectx, char *value, size_t end)
// {
// 	size_t var_value_len;
// 	size_t old_size;
// 	size_t new_size;
// 	char *new_input;

// 	var_value_len = ft_strlen(value);
// 	old_size = ft_strlen(ectx->s);
// 	new_size = (old_size + (var_value_len - (end - ectx->offset)));
// 	if (new_size > old_size)
// 	{
// 		new_input = ft_realloc(ectx->s, old_size, (new_size + 1));
// 		ectx->s = new_input;
// 		if (!ectx->s)
// 			return (handle_err(msh, (t_err){T_SYS_ERR, MALLOC}, false), ERROR);
// 	}
// 	ft_memmove((ectx->s + ectx->offset + var_value_len),
// 			   ectx->s + end, old_size - end);
// 	ft_memcpy(ectx->s + ectx->offset, value, var_value_len);
// 	ectx->s[new_size] = '\0';
// 	return (var_value_len);
// }

// static size_t extract_env_var_value(t_msh **msh, t_ctx *ectx, char end_char)
// {
// 	size_t start;
// 	size_t end;
// 	char *name;
// 	char *value;
// 	bool is_in_brackets;

// 	start = ectx->offset + (ectx->s[ectx->offset] == T_VAR_EXP);
// 	is_in_brackets = ectx->s[start] == T_CURLY_OPEN;
// 	if (ectx->s[start] == T_CURLY_OPEN)
// 		ft_memmove(&ectx->s[start], &ectx->s[start + 1], ectx->s_len--);
// 	end = start;
// 	name = NULL;
// 	value = NULL;
// 	while (ectx->s[end] && ectx->s[end] != end_char)
// 	{
// 		if (!value && ectx->s[end] == '?' && end_char == T_CURLY_CLOSE)
// 			value = ft_itoa((*msh)->exit_code);
// 		end++;
// 		if (!ft_isalnum(ectx->s[end]) && !ft_strchr("_?", ectx->s[end]))
// 			break;
// 	}
// 	if (end_char != T_SPACE)
// 		ft_memmove(&ectx->s[end], &ectx->s[end + 1], ectx->s_len--);
// 	if (value)
// 		return (update_input(msh, ectx, value, end));
// 	name = ft_substr(ectx->s, start, (end - start));
// 	value = get_env_var((*msh)->env_vars, name);
// 	return (update_input(msh, ectx, value, end));
// }

void *ft_memcpy2(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

void *ft_memmove2(void *dst, const void *src, size_t len)
{
	if (dst == src)
		return (dst);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len--)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	}
	return (dst);
}

static int update_input(t_msh **msh, t_ctx *ectx, size_t end)
{
	size_t len;
	size_t old_size;
	size_t new_size;
	char *new_input;

	len = ft_strlen(ectx->value);
	old_size = ectx->input_len;
	new_size = (old_size + (len - (end - ectx->offset)));
	if (new_size > old_size)
	{
		new_input = ft_realloc((*ectx->input), (old_size + 1), (new_size + 1));
		if (!new_input)
			return (handle_err(msh, (t_err){T_SYS_ERR, MALLOC}, false), ERROR);
		new_input[new_size] = '\0';
		ectx->input_len = new_size;
		(*ectx->input) = new_input;
		ectx->s = (new_input + ectx->index);
	}
	ft_memmove2((ectx->s + len), ectx->s + (end - ectx->offset), (old_size - ectx->index) - (end - ectx->offset) + 1);
	ft_memcpy2(ectx->s, ectx->value, len);
	ectx->s += len;
	ectx->index += len;
	return (SUCCESS);
}

static char	*get_env_var_input(t_ctx *ectx, char end_char)
{
	int	i;

	i = 0;
	while (ectx->s[i] && ectx->s[i] != end_char)
		i++;
	ectx->s[i] = '\0';
	return (ectx->s);
}

static int	process_env_var(t_msh **msh, t_ctx *ectx, char end_char)
{
	int	start;
	int	end;

	start = ectx->offset + (ectx->s[ectx->offset] == T_VAR_EXP);
	end = start;
	if (!ft_isalnum(ectx->s[end]) && ectx->s[end] != '?')
		return (handle_err(msh, (t_err){T_OTHER_ERR,
				UNEXPECTED_EOF_TOK_MSG, &ectx->s[end]}, false), ERROR);
	if (ectx->s[end] == '?')
	{
		ectx->value = ft_itoa((*msh)->exit_code);
		if (update_input(msh, ectx, ++end) == ERROR)
			return (free(ectx->value), ERROR);
		return (free(ectx->value), SUCCESS);
	}
	while (ectx->s[end] && ectx->s[end] != end_char)
	{
		if (!ft_isalnum(ectx->s[end]))
			break ;
		end++;
	}
	ectx->name = ft_substr(ectx->s, start, end - start);
	ectx->value = get_env_var((*msh)->env_vars, ectx->name);
	if (update_input(msh, ectx, end) == ERROR)
		return (free(ectx->name), ERROR);
	return (free(ectx->name), SUCCESS);
}

static int	process_enclosed_input(t_msh **msh, t_ctx *ectx, char end_char)
{
	int	i;

	i = (*ectx->s) == end_char;
	while (ectx->s[i] && ectx->s[i] != end_char)
	{
		if (end_char != T_SINGLE_QUOTE && ectx->s[i] == T_VAR_EXP)
		{
			ectx->offset = i;
			ectx->index += i;
			if (process_env_var(msh, ectx, end_char) == ERROR)
				return (ERROR);
			i = 0;
			if (!ectx->s[i])
				break ;
		}
		i++;
	}
	ectx->index += i + (ectx->s[i] != '\0');
	ectx->s += i + (ectx->s[i] != '\0');
	return (SUCCESS);
}

int	exp_env_var(t_msh **msh, bool is_input_enclosed)
{
	t_ctx	ectx;

	ectx = (t_ctx){(&(*msh)->input), 0, (*msh)->input, 0, 0, 0, NULL, NULL};
	ectx.input_len = ft_strlen((*msh)->input);
	ectx.s_len = ectx.input_len;
	if (is_input_enclosed)
		return (process_enclosed_input(msh, &ectx, T_SPACE));
	while ((*ectx.s))
	{
		if ((*ectx.s) == T_SINGLE_QUOTE || (*ectx.s) == T_DOUBLE_QUOTE)
		{
			if (process_enclosed_input(msh, &ectx, (*ectx.s)) == ERROR)
				return (ERROR);
		}
		if ((*ectx.s) == T_VAR_EXP)
		{
			if (process_env_var(msh, &ectx, T_SPACE) == ERROR)
				return (ERROR);
		}
		if (!(*ectx.s))
			break ;
		ectx.index++;
		ectx.s++;
	}
	return (SUCCESS);
}

// static int	validate_env_var(t_msh **msh, const char *s, char end_char)
// {
// 	int		i;

// 	i = (*s) == T_VAR_EXP;
// 	if (s[i] == T_CURLY_OPEN || s[i] == T_SQUARE_OPEN || s[i] == T_BRACKET_OPEN)
// 	{
// 		end_char = (s[i] + 2) - (s[i] == T_BRACKET_OPEN);
// 		i++;
// 	}
// 	if (s[i])
// 	{
// 		if (end_char == T_CURLY_CLOSE && !ft_isalpha(s[i]) && s[i++] != '_')
// 			return (handle_err(msh, (t_err){T_BAD_REQUEST_ERR,
// 					(char *)s, BAD_SUBST_MSG}, false), ERROR);
// 	}
// 	while (s[i] && s[i] != end_char)
// 		i++;
// 	if (end_char != T_SPACE && s[i] != end_char)
// 	{
// 		handle_err(msh, (t_err){T_OTHER_ERR,
// 			UNEXPECTED_EOF_TOK_MSG, tokstr(end_char)}, false);
// 		return (handle_err(msh, (t_err){T_OTHER_ERR,
// 				SYNTAX_ERR_MSG, UNEXPECTED_EOF_MSH}, false), ERROR);
// 	}
// 	return (!(end_char != T_SPACE && s[i] != end_char));
// }

// static size_t	extract_env_var(t_msh **msh, t_val *ectx, t_val *sctx)
// {
// 	size_t	start;
// 	size_t	end;
// 	char	*var_name;
// 	size_t	var_name_len;
// 	char	*var_value;
// 	size_t	var_value_len;
// 	size_t	old_size;
// 	size_t	new_size;

// 	start = ectx->offset + ((*ectx->s)[ectx->offset] == T_VAR_EXP);
// 	if ((*ectx->s)[start] == '{')
// 	{
// 		ectx->end_char = '}';
// 		start++;
// 	}
// 	end = start;
// 	var_name = NULL;
// 	var_value = NULL;
// 	while ((*ectx->s)[end])
// 	{
// 		if (!ft_isalnum((*ectx->s)[end]) && !ft_strchr("_?", (*ectx->s)[end]))
// 			break ;
// 		if ((*ectx->s)[end] == '?')
// 		{
// 			var_value = ft_itoa(((*msh)->exit_code));
// 			end++;
// 			break ;
// 		}
// 		end++;
// 	}
// 	if (ectx->end_char != T_SPACE && (*ectx->s)[end] == ectx->end_char)
// 		ft_memmove(&(*ectx->s)[end], &((*ectx->s)[end + 1]), sctx->len);
// 	if (!var_value)
// 	{
// 		var_name = ft_substr((*ectx->s), start, (end - start));
// 		var_name_len = end - ectx->offset;
// 		var_value = get_env_var((*msh)->env_vars, var_name);
// 	}
// 	var_value_len = ft_strlen(var_value);
// 	old_size = ft_strlen((*ectx->s));
// 	new_size = (old_size + (var_value_len - (end - ectx->offset)));
// 	if (new_size > old_size)
// 	{
// 		char *new_value = ft_realloc((*ectx->s), old_size, (new_size + 1));
// 		(*ectx->s) = new_value;
// 		if (!(*ectx->s))
// 			return (handle_err(msh, (t_err){T_SYS_ERR,
// 					MALLOC}, false), free(var_name), ERROR);
// 	}
// 	ft_memmove(((*ectx->s) + ectx->offset + var_value_len), (*ectx->s) + end, old_size - end);
// 	ft_memcpy((*ectx->s) + ectx->offset, var_value, var_value_len);
// 	(*ectx->s)[new_size] = '\0';
// 	if (var_name)
// 		free(var_name);
// 	else
// 		free(var_value);
// 	sctx->len = ft_strlen((*ectx->s));
// 	sctx->offset += end - ectx->offset;
// 	return (var_value_len);
// }

// int	exp_env_var(t_msh **msh, t_val *sctx, int offset)
// {
// 	t_val	ectx;
// 	int		is_env_var_valid;

// 	if (!(*sctx->s) || is_emptystr((*sctx->s)))
// 		return (0);
// 	ectx = (t_val){(sctx->s), ft_strlen((*sctx->s)), offset, false, T_SPACE};
// 	is_env_var_valid = validate_env_var(msh, &(*sctx->s)[offset], T_SPACE);
// 	if (!is_env_var_valid)
// 		return (0);
// 	if (is_env_var_valid == ERROR)
// 		return (ERROR);
// 	ectx = (t_val){(sctx->s), ft_strlen((*sctx->s)), offset, false, T_SPACE};
// 	offset = extract_env_var(msh, &ectx, sctx);
// 	if (offset == ERROR)
// 		return (ERROR);
// 	return (offset);
// }
