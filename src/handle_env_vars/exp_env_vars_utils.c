/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_vars_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:34:55 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/04 16:15:25 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_input(t_msh **msh, t_ctx *ectx, size_t end);

bool	is_tilda_expandable(char *s, int i)
{
	char	prev_char;
	char	next_char;

	prev_char = '\0';
	next_char = '\0';
	if (i > 0 && s[i - 1])
		prev_char = s[i - 1];
	if (s[i + 1])
		next_char = s[i + 1];
	if ((prev_char && !ft_isspace(prev_char)))
		return (false);
	if (next_char && next_char != '/' && !ft_isspace(next_char))
		return (false);
	return (true);
}

int	handle_special_chars(t_msh **msh, t_ctx *ectx, int i)
{
	if (ectx->s[i] == '?')
	{
		ectx->value = ft_itoa((*msh)->exit_code);
		if (update_input(msh, ectx, ++i) == ERROR)
			return (free(ectx->value), ERROR);
		return (free(ectx->value), SUCCESS);
	}
	if (ectx->s[i] == '~' && !ectx->is_in_quotes)
	{
		if (is_tilda_expandable(ectx->s, i))
		{
			ectx->value = get_env_var((*msh)->env_vars, "HOME");
			if (update_input(msh, ectx, ++i) == ERROR)
				return (ERROR);
		}
	}
	ectx->s += (*ectx->s) != '\0';
	ectx->offset += (*ectx->s) != '\0';
	return (SUCCESS);
}

void	process_env_var_quotes(t_ctx *ectx, char *c)
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

bool	is_env_var_expandable(t_ctx ectx, char *s)
{
	if ((*s) != '$' && (*s) != '~')
		return (false);
	if (ectx.end_char == T_SINGLE_QUOTE)
		return (false);
	if ((*s) == '~' && !ectx.is_in_quotes)
		return (true);
	if ((*(s + 1)) == ectx.end_char || (*(s + 1)) == T_SPACE)
		return (false);
	if (!ectx.is_in_quotes && ectx.is_redir)
		return (false);
	return (true);
}
