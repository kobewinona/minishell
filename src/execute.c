/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:43:14 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/12 11:14:56 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char **argv)
{
	if (ft_strncmp(argv[0], "echo", ft_strlen("echo")) == 0)
		echo(argv);
	else
		exec_path_cmd(argv);
}
