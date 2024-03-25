/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:56:52 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/25 18:43:37 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_readline_disconnect(t_msh **msh, int org_fd, char *input)
{
	if (!input)
	{
		if (dup2(org_fd, STDIN_FILENO) == ERROR)
			return (handle_err(msh, SYSTEM, DUP2, 1), true);
		return (true);
	}
	return (false);
}

static int	update_collected_input(t_msh **msh, char **dest, char *value)
{
	char	*temp;

	temp = ft_strjoin((*dest), value);
	if (!temp)
		return (handle_err(msh, SYSTEM, MALLOC, 1), ERROR);
	free((*dest));
	(*dest) = temp;
	temp = ft_strjoin((*dest), "\n");
	if (!temp)
		return (handle_err(msh, SYSTEM, MALLOC, 1), ERROR);
	free((*dest));
	(*dest) = temp;
	return (SUCCESS);
}

static int	collect_input(t_msh **msh, char **dest, char *eof, char *prompt)
{
	char	*input;
	int		org_fd;

	org_fd = dup(STDIN_FILENO);
	if (org_fd < 0)
		return (handle_err(msh, SYSTEM, DUP, 1), ERROR);
	input = readline(prompt);
	if (handle_readline_disconnect(msh, org_fd, input))
		return (ERROR);
	while (input)
	{
		if (!ft_strncmp(input, eof, ft_strlen(eof)))
			break ;
		if (update_collected_input(msh, dest, input) == ERROR)
			return (free(input), ERROR);
		free(input);
		input = readline(prompt);
		if (handle_readline_disconnect(msh, org_fd, input))
			return (ERROR);
	}
	return (free(input), SUCCESS);
}

char	*collect_heredoc_input(t_msh **msh, char *eof)
{
	char	*heredoc_input;

	if (!eof)
		return (handle_err(msh, UNEXPECTED_TOK, "newline", 2), NULL);
	heredoc_input = ft_strdup("");
	if (!heredoc_input)
		return (handle_err(msh, SYSTEM, MALLOC, 1), NULL);
	g_state = IS_IN_HEREDOC;
	if (collect_input(msh, &heredoc_input, eof, INPUT_PROMPT) == ERROR)
	{
		g_state = IS_IDLE;
		return (free(heredoc_input), NULL);
	}
	g_state = IS_IDLE;
	if (exp_env_vars(msh, &heredoc_input, true) == ERROR)
		return (NULL);
	return (heredoc_input);
}
