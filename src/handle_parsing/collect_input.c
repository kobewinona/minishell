/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:56:52 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/19 12:26:28 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	collect_input(char **dest, const char *eof, char *input_prompt)
{
	char	*tty_input;
	char	*temp;

	tty_input = readline(input_prompt);
	while (tty_input)
	{
		if (!ft_strncmp(tty_input, eof, ft_strlen(eof)))
			break ;
		temp = ft_strjoin((*dest), tty_input);
		free((*dest));
		(*dest) = temp;
		temp = ft_strjoin((*dest), "\n");
		free((*dest));
		(*dest) = temp;
		free(tty_input);
		tty_input = readline(input_prompt);
	}
	free(tty_input);
}

char	*collect_heredoc_input(t_msh **msh, const char *eof)
{
	char	*heredoc_input;

	if (!eof)
		return (handle_err(msh, (t_err){T_OTHER_ERR,
				UNEXPECTED_TOK_MSG, NEWLINE}, false), NULL);
	heredoc_input = ft_strdup("");
	if (!heredoc_input)
		return (handle_err(msh, (t_err){T_SYS_ERR, MALLOC}, false), NULL);
	collect_input(&heredoc_input, eof, INPUT_PROMPT);
	if (exp_env_var(msh, &heredoc_input, true) == ERROR)
		return (NULL);
	return (heredoc_input);
}
