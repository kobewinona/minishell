/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:15:21 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/15 09:37:31 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_env_var(t_msh **msh, const char *s, char end_char)
{
	int		i;

	i = (*s) == T_VAR_EXP;
	if (s[i] == T_CURLY_OPEN || s[i] == T_SQUARE_OPEN || s[i] == T_BRACKET_OPEN)
	{
		end_char = (s[i] + 2) - (s[i] == T_BRACKET_OPEN);
		i++;
	}
	if (s[i])
	{
		if (end_char == T_CURLY_CLOSE && !ft_isalpha(s[i]) && s[i++] != '_')
			return (handle_err(msh, (t_err){T_BAD_REQUEST_ERR,
					(char *)s, BAD_SUBST_MSG}, false), ERROR);
	}
	while (s[i] && s[i] != end_char)
		i++;
	if (end_char != T_SPACE && s[i] != end_char)
	{
		handle_err(msh, (t_err){T_OTHER_ERR,
			UNEXPECTED_EOF_TOK_MSG, tokstr(end_char)}, false);
		return (handle_err(msh, (t_err){T_OTHER_ERR,
				SYNTAX_ERR_MSG, UNEXPECTED_EOF_MSH}, false), ERROR);
	}
	return (!(end_char != T_SPACE && s[i] != end_char));
}

static size_t	extract_env_var(t_msh **msh, t_val *ectx, t_val *sctx)
{
	size_t	start;
	size_t	end;
	char	*var_name;
	size_t	var_name_len;
	char	*var_value;
	size_t	var_value_len;
	size_t	old_size;
	size_t	new_size;

	start = ectx->offset + ((*ectx->s)[ectx->offset] == T_VAR_EXP);
	if ((*ectx->s)[start] == '{')
	{
		ectx->end_char = '}';
		start++;
	}
	end = start;
	while ((*ectx->s)[end])
	{
		if (!ft_isalnum((*ectx->s)[end]) && (*ectx->s)[end] != '_')
			break ;
		end++;
	}
	if (ectx->end_char != T_SPACE && (*ectx->s)[end] == ectx->end_char)
		ft_memmove(&(*ectx->s)[end], &((*ectx->s)[end + 1]), sctx->len);
	var_name = ft_substr((*ectx->s), start, (end - start));
	var_name_len = end - ectx->offset;
	var_value = get_env_var((*msh)->env_vars, var_name);
	var_value_len = ft_strlen(var_value);
	old_size = ft_strlen((*ectx->s));
	new_size = (old_size + (var_value_len - (end - ectx->offset)));
	if (new_size > old_size)
	{
		char *new_value = ft_realloc((*ectx->s), old_size, (new_size + 1));
		(*ectx->s) = new_value;
		if (!(*ectx->s))
			return (handle_err(msh, (t_err){T_SYS_ERR,
					MALLOC}, false), free(var_name), ERROR);
	}
	(*ectx->s)[new_size] = '\0';
	ft_memmove(((*ectx->s) + ectx->offset + var_value_len), (*ectx->s) + end, old_size - end);
	ft_memcpy((*ectx->s) + ectx->offset, var_value, var_value_len);
	free(var_name);
	sctx->len = ft_strlen((*ectx->s));
	sctx->offset += end - ectx->offset;
	return (var_value_len);
}

int	exp_env_var(t_msh **msh, t_val *sctx, int offset)
{
	t_val	ectx;
	int		is_env_var_valid;

	if (!(*sctx->s) || is_emptystr((*sctx->s)))
		return (0);
	ectx = (t_val){(sctx->s), ft_strlen((*sctx->s)), offset, false, T_SPACE};
	is_env_var_valid = validate_env_var(msh, &(*sctx->s)[offset], T_SPACE);
	if (!is_env_var_valid)
		return (0);
	if (is_env_var_valid == ERROR)
		return (ERROR);
	ectx = (t_val){(sctx->s), ft_strlen((*sctx->s)), offset, false, T_SPACE};
	offset = extract_env_var(msh, &ectx, sctx);
	if (offset == ERROR)
		return (ERROR);
	return (offset);
}
