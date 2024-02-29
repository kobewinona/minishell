/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:26:56 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/27 14:15:57 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*collect_heredoc_input(t_msh **msh, const char *eof)
{
	char	*heredoc_input;
	char	*tty_input;
	char	*temp;

	if (!eof)
	{
		log_err(msh, T_SYNTAX_ERR, UNEXPECTED_TOK_MSG, NEWLINE);
		return (NULL);
	}
	heredoc_input = ft_strdup("");
	tty_input = readline(INPUT_PROMPT);
	while (tty_input)
	{
		if (!ft_strncmp(tty_input, eof, ft_strlen(eof)))
			break ;
		temp = ft_strjoin(heredoc_input, tty_input);
		free(heredoc_input);
		heredoc_input = temp;
		temp = ft_strjoin(heredoc_input, "\n");
		free(heredoc_input);
		heredoc_input = temp;
		free(tty_input);
		tty_input = readline(INPUT_PROMPT);
	}
	free(tty_input);
	return (heredoc_input);
}

static int	nullterminate(t_msh **msh, char **s, int end, char end_chr)
{
	if (end_chr != ' ' && (*s)[end] != end_chr)
	{
		log_err(msh, T_SYNTAX_ERR, UNEXPECTED_EOF_MSG, tokstr(end_chr));
		return (ERROR);
	}
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
	return (SUCCESS);
}

int	get_arb_fd(char **s)
{
	int	fd;
	int	i;

	i = (int)ft_strlen(*s) - 1;
	if ((*s) && !is_emptystr(*s))
	{
		while ((*s) && !ft_isspace((*s)[i]))
			i--;
		fd = ft_atoi(&(*s)[i]);
		if (fd > 0)
			(*s)[i] = '\0';
	}
	return (fd);
}

char	*get_value(t_msh **msh, char **s)
{
	char	*value;
	char	end_chr;
	int		end;

	if (!*s)
		return (NULL);
	value = NULL;
	end_chr = ' ';
	end = 0;
	while (**s && ft_isspace(**s))
		(*s)++;
	value = (*s);
	while (!ft_isspace((*s)[end]))
	{
		if ((*s)[end] == T_DOUBLE_QUOTE || (*s)[end] == T_SINGLE_QUOTE)
		{
			end_chr = (*s)[end];
			end++;
		}
		while ((*s)[end] && (*s)[end] != end_chr)
			end++;
		if ((*s)[end] == end_chr)
			(*s)[end] = (*s)[end + 1];
	}
	if (nullterminate(msh, s, end, end_chr) == ERROR)
		return (NULL);
	if (!is_emptystr(value))
		return (value);
	return (NULL);
}

//char	*get_value(t_msh **msh, char **s)
//{
//	char	*value;
//	char	end_chr;
//	int		end;
//
//	if (!*s)
//		return (NULL);
//	end_chr = ' ';
//	end = 0;
//	while (**s && ft_isspace(**s))
//		(*s)++;
//	value = (*s);
//	if (**s == T_DOUBLE_QUOTE || **s == T_SINGLE_QUOTE)
//	{
//		end_chr = *(*s)++;
//		end++;
//	}
//	while ((*s)[end])
//	{
//		if ((*s)[end] == end_chr)
//			break ;
//		end++;
//	}
//	if (nullterminate(msh, s, end, end_chr) == ERROR)
//		return (NULL);
//	if (!is_emptystr(value))
//		return (value);
//	return (NULL);
//}

int	populate_argv(t_msh **msh, char **argv, char *input)
{
	int		index;

	if (!input)
		return (ERROR);
	index = 0;
	while (argv && argv[index])
		index++;
	while (!is_emptystr(input))
	{
		argv[index] = get_value(msh, &input);
		if (!argv[index])
			return (ERROR);
		argv[index] = ft_strtrim(argv[index], "\"\'");
		if (!argv[index])
		{
			free_array(argv);
			log_err(msh, T_SYS_ERR, MALLOC, NULL);
			return (ERROR);
		}
		index++;
	}
	return (SUCCESS);
}
