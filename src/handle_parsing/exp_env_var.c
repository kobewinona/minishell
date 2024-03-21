/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:15:21 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 01:26:22 by dklimkin         ###   ########.fr       */
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
	new_size = (old_size + (len - (end - ectx->offset)));
	if (new_size > old_size)
	{
		new_input = ft_realloc((*ectx->input), (old_size + 1), (new_size + 1));
		if (!new_input)
			return (handle_err(msh, SYSTEM, MALLOC, 1), ERROR);
		new_input[new_size] = '\0';
		ectx->input_len = new_size;
		(*ectx->input) = new_input;
	}
	ectx->s = ((*ectx->input) + ectx->index);
	move_len = (old_size - ectx->index) - (end - ectx->offset) + 1;
	ft_memmove((ectx->s + len), ectx->s + (end - ectx->offset), move_len);
	ft_memcpy(ectx->s, ectx->value, len);
	ectx->s += len;
	ectx->index += len;
	return (SUCCESS);
}

static int	process_env_var(t_msh **msh, t_ctx *ectx)
{
	int	start;
	int	end;

	if (ectx->iseof)
		return (ectx->iseof = false, ++(ectx->index), ++(ectx->s), SUCCESS);
	start = ectx->offset + (ectx->s[ectx->offset] == T_VAR_EXP);
	end = start;
	if (!ft_isalnum(ectx->s[end]) && ectx->s[end] != '?')
		return (handle_err(msh, UNEXPECTED_TOK, &ectx->s[end], 2), ERROR);
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
			if (process_env_var(msh, ectx) == ERROR)
				return (ERROR);
			i = -1;
		}
		i++;
	}
	ectx->index += i + (ectx->s[i] != '\0');
	ectx->s += i + (ectx->s[i] != '\0');
	return (ectx->offset = 0, SUCCESS);
}

int	exp_env_var(t_msh **msh, char **input, bool is_input_enclosed)
{
	t_ctx	ectx;

	ectx = (t_ctx){input, ft_strlen((*input)), (*input), 0, 0, NULL, NULL, 0};
	if (is_input_enclosed)
		return (process_enclosed_input(msh, &ectx, T_SPACE));
	while ((*ectx.s))
	{
		ectx.iseof = ((*ectx.s) == '<' && (*(ectx.s + 1)) == '<') - ectx.iseof;
		if ((*ectx.s) == T_SINGLE_QUOTE || (*ectx.s) == T_DOUBLE_QUOTE)
		{
			if (process_enclosed_input(msh, &ectx, (*ectx.s)) == ERROR)
				return (ERROR);
		}
		if ((*ectx.s) == T_VAR_EXP)
		{
			if (process_env_var(msh, &ectx) == ERROR)
				return (ERROR);
			continue ;
		}
		if (!(*ectx.s))
			break ;
		ectx.index++;
		ectx.s++;
	}
	return (SUCCESS);
}
