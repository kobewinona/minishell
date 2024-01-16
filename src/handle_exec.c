/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:11:26 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/16 16:11:27 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exec(t_exec *exec)
{
	if (ft_strncmp(exec->argv[0], ECHO, ft_strlen(ECHO)) == 0)
		echo(exec->argv);
	else if (ft_strncmp(exec->argv[0], PWD, ft_strlen(PWD)) == 0)
		pwd(exec->argv);
	else
		exec_ext_cmd(exec->argv);
}
