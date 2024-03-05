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

void	handle_cd(const char *input, t_var_node *env_vars)
{
	char	**argv;
	int		i;

	argv = NULL;
	argv = ft_split(input, ' ');
	if (!argv)
		return ;
	if (argv[0] && !ft_strncmp(argv[0], CD, ft_strlen(CD)))
		cd(argv[1], env_vars);
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
