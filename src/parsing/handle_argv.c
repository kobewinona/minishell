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

static void	*cleanup_argv_on_exit(char **argv)
{
	int	index;

	index = 0;
	while (argv[index])
	{
		free(argv[index]);
		index++;
	}
	free(argv);
	return (NULL);
}

static void	update_end(char *s, int *end, char end_chr)
{
	while (s[*end] && s[*end] != end_chr)
		(*end)++;
	if (end_chr != '\0' && end_chr != ' ')
	{
		if (s[*end] != end_chr)
			handle_err(ERROR, (t_err){T_SYNTAX_ERR, UNEXPECTED_EOF_MSG,
				tokstr(end_chr)}, true);
	}
}

static size_t	get_value(char **dest, char *s)
{
	int		start;
	int		end;
	char	quote_tok;

	start = 0;
	end = start;
	quote_tok = '\0';
	if (s[end] == '\"' || s[end] == '\'')
	{
		quote_tok = s[end++];
		start = end;
		update_end(s, &end, quote_tok);
	}
	else
		update_end(s, &end, ' ');
	*dest = ft_substr(s, start, (end - start));
	if (!*dest)
		handle_err(ERROR, (t_err){T_SYS_ERR, NULL, MALLOC}, true);
	*dest = ft_strtrim(*dest, "\"\'");
	if (quote_tok != '\0')
		return (end + 1);
	return (end);
}

char	**parse_argv(char *input)
{
	char	**argv;
	int		index;

	if (!input)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * 1);
	if (!argv)
		handle_err(ERROR, (t_err){T_SYNTAX_ERR, NULL, MALLOC}, true);
	index = 0;
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input != '\0')
		{
			input += get_value(&argv[index], input);
			if (!argv[index] && index == 0)
				return (cleanup_argv_on_exit(argv));
			index++;
			argv = ft_realloc(argv, sizeof(char *) * index,
					sizeof(char *) * (index + 1));
		}
	}
	argv[index] = NULL;
	return (argv);
}
