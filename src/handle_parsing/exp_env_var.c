/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:15:21 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/14 04:24:31 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_env_var_valid(t_msh **msh, const char *s)
{
	char	end_char;
	int		i;

	end_char = T_SPACE;
	i = (*s) == T_VAR_EXP;
	if (s[i] == '{')
	{
		end_char = '}';
		i++;
	}
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (handle_err(msh, (t_err){T_BAD_REQUEST_ERR,
				(char *)s, BAD_SUBST_MSG}, false), false);
	i++;
	while (s[i] && s[i] != end_char)
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (!(end_char == '}' && s[i] != end_char));
}

// 10
// 14
// s $HOME e" // 10
// s /home/dklimkin e" // 19

// $HOME e" // 8
// /home/dklimkin e" // 17

// $HOME e"000000

static size_t	extract_env_var(t_msh **msh, t_val *ctx)
{
	size_t	start;
	size_t	end;
	char	*var_name;
	char	*var_value;
	size_t	var_value_len;

	start = *(*ctx->s) == T_VAR_EXP;
	if ((*ctx->s)[start] == '{')
	{
		ctx->end_char = '}';
		start++;
	}
	end = start;
	while ((*ctx->s)[end])
	{
		if ((*ctx->s)[end] == ctx->end_char)
			break ;
		end++;
	}
	var_name = ft_substr((*ctx->s), start, (end - start));
	var_value = get_env_var((*msh)->env_vars, var_name);
	var_value_len = ft_strlen(var_value);
	size_t old_size = ft_strlen((*msh)->input);
	size_t new_size = (old_size + (var_value_len - end));
	int offset = (*ctx->s) - (*msh)->input;
	(*msh)->input = ft_realloc((*msh)->input, old_size, (new_size + 1));
	(*msh)->input[new_size] = '\0';
	(*ctx->s) = (*msh)->input + offset;
	if (!(*ctx->s))
	{
		free(var_name);
		return (ERROR);
	}
	ft_memmove(((*ctx->s) + (var_value_len - end)), (*ctx->s), ft_strlen((*ctx->s)));
	ft_memcpy((*ctx->s), var_value, var_value_len);
	free(var_name);
	return (var_value_len);
}

size_t	exp_env_var(t_msh **msh, char *s)
{
	t_val	ctx;
	size_t	len;

	if (!s || is_emptystr(s))
		return (ERROR);
	while (ft_isspace((*s)))
		s++;
	if (!is_env_var_valid(msh, s))
		return (ERROR);
	ctx = (t_val){&s, ft_strlen(s), false, T_SPACE};
	len = extract_env_var(msh, &ctx);
	if (len == ERROR)
		return (ERROR);
	s += len;
	return (len);
}
