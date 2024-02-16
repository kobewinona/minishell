/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:26:56 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/13 12:26:56 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	nullterminate(char **s, int end, char end_chr)
{
	if (end_chr != ' ' && (*s)[end] != end_chr)
		handle_err(ERROR, (t_err){T_SYNTAX_ERR,
			UNEXPECTED_EOF_MSG, tokstr(end_chr)}, true);
	if ((*s)[end] == end_chr)
	{
		(*s)[end] = '\0';
		end++;
	}
	(*s) += end;
	if (end_chr == T_DOUBLE_QUOTE || end_chr == T_SINGLE_QUOTE)
	{
		if ((**s) == end_chr)
			(*s) += 1;
	}
}


char	*get_value(char **s)
{
	char	*value;
	char	end_chr;
	int		end;

	end_chr = ' ';
	end = 0;
	while (**s && ft_isspace(**s))
		(*s)++;
	value = (*s);
	if (**s == T_DOUBLE_QUOTE || **s == T_SINGLE_QUOTE)
	{
		end_chr = *(*s)++;
		end++;
	}
	while ((*s)[end])
	{
		if ((*s)[end] == end_chr)
			break ;
		end++;
	}
	nullterminate(s, end, end_chr);
	if (!is_emptystr(value))
		return (value);
	return (NULL);
}

void	populate_argv(char **argv, char *input)
{
	int		index;

	if (!input)
		return ;
	index = 0;
	while (argv && argv[index])
		index++;
	while (!is_emptystr(input))
	{
		argv[index] = get_value(&input);
		if (argv[index])
			argv[index] = ft_strtrim(argv[index], "\"\'");
		index++;
	}
}
