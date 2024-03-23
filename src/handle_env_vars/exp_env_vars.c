/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 02:03:55 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/23 07:00:26 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_input(t_msh **msh, t_ctx *ectx, size_t end)
{
	size_t	len;
	size_t	old_size;
	size_t	new_size;
	char	*new_input;
	size_t	move_len;

	len = ft_strlen(ectx->value);
	old_size = ectx->input_len;
	new_size = (old_size + (len - end));
	if (new_size > old_size)
	{
		new_input = ft_realloc((*ectx->input), (old_size + 1), (new_size + 1));
		if (!new_input)
			return (handle_err(msh, SYSTEM, MALLOC, 1), ERROR);
		new_input[new_size] = '\0';
		ectx->input_len = new_size;
		(*ectx->input) = new_input;
	}
	ectx->s = ((*ectx->input) + ectx->offset);
	move_len = (old_size - ectx->offset) - end + 1;
	ft_memmove((ectx->s + len), ectx->s + end, move_len);
	ft_memcpy(ectx->s, ectx->value, len);
	ectx->s += len;
	ectx->offset += len;
	return (SUCCESS);
}

static int	exp_env_var(t_msh **msh, t_ctx *ectx)
{
	int		start;
	int		end;
	char	*err_ctx;

	start = (*ectx->s) == '$';
	end = start;
	if (!ft_isalnum(ectx->s[end]) && ectx->s[end] != '?')
	{
		err_ctx = char_to_str(&ectx->s[end]);
		return (handle_err(msh, UNEXPECTED_TOK, err_ctx, 2), ERROR);
	}
	if (ectx->s[end] == '?')
	{
		ectx->value = ft_itoa((*msh)->exit_code);
		if (update_input(msh, ectx, ++end) == ERROR)
			return (free(ectx->value), ERROR);
		return (free(ectx->value), SUCCESS);
	}
	while (ectx->s[end] && (ft_isalnum(ectx->s[end]) || ectx->s[end] == '_'))
		end++;
	ectx->name = ft_substr(ectx->s, start, end - start);
	ectx->value = get_env_var((*msh)->env_vars, ectx->name);
	return (free(ectx->name), update_input(msh, ectx, end));
}

static void	process_quotes(t_ctx *ectx, char *c)
{
	if (!ectx->is_in_quotes)
	{
		(ectx->is_in_quotes) = (*c) == T_DOUBLE_QUOTE || (*c) == T_SINGLE_QUOTE;
		if (ectx->is_in_quotes)
			ectx->end_char = (*c);
		return ;
	}
	if (ectx->is_in_quotes && (*c) == ectx->end_char)
	{
		ectx->is_in_quotes = false;
		ectx->end_char = T_SPACE;
		ectx->is_redir = false;
	}
}

static bool	is_expandable(t_ctx ectx, char *s)
{
	if ((*s) != '$')
		return (false);
	if (ectx.end_char == T_SINGLE_QUOTE)
		return (false);
	if (!(*(s + 1)))
		return (false);
	if ((*(s + 1)) == ectx.end_char || (*(s + 1)) == T_SPACE)
		return (false);
	if (!ectx.is_in_quotes && ectx.is_redir)
		return (false);
	return (true);
}

int	exp_env_vars(t_msh **msh, char **input)
{
	t_ctx	ectx;

	ectx = (t_ctx){NULL, ft_strlen((*input)), NULL, 0, NULL, NULL, 0, 0, 0};
	ectx.input = input;
	ectx.s = (*input);
	ectx.end_char = T_SPACE;
	while ((*ectx.s))
	{
		process_quotes(&ectx, &(*ectx.s));
		if (!ectx.is_redir && !ectx.is_in_quotes)
			ectx.is_redir = (*ectx.s) == '>' || (*ectx.s) == '<';
		if (is_expandable(ectx, ectx.s))
		{
			if (exp_env_var(msh, &ectx) == ERROR)
				return (ERROR);
			process_quotes(&ectx, &(*ectx.s));
			if (ectx.is_redir)
				ectx.is_redir -= !ectx.is_in_quotes;
		}
		if (!(*ectx.s))
			break ;
		ectx.offset++;
		ectx.s++;
	}
	return (SUCCESS);
}
