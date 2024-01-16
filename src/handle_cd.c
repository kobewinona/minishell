/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:53:56 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/16 23:53:57 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup(char ***argv)
{
	int	i;

	i = 0;
	while ((*argv)[i])
	{
		free((*argv)[i]);
		i++;
	}
	free((*argv));
}

static char	*get_cd_path(const char *input)
{
	char	**argv;
	char	*path;

	argv = ft_split(input, ' ');
	if (!argv)
		return (NULL);
	if (!argv[0])
	{
		cleanup(&argv);
		return (NULL);
	}
	if (ft_strncmp(argv[0], CD, ft_strlen(CD)) == 0 && argv[1] != NULL)
	{
		path = ft_strdup(argv[1]);
		cleanup(&argv);
		return (path);
	}
	cleanup(&argv);
	return (NULL);
}

void	handle_cd(const char *input)
{
	char	*path;

	path = get_cd_path(input);
	cd(path);
	free(path);
}
