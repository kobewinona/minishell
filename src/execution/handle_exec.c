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

void	handle_exec(t_exec *params)
{
	if (ft_strncmp(params->argv[0], CD, ft_strlen(CD)))
	{
		if (!ft_strncmp(params->argv[0], ECHO, ft_strlen(ECHO)))
			return ;
		else if (!ft_strncmp(params->argv[0], PWD, ft_strlen(PWD)))
			return ;
		else
			handle_ext_cmd(params->argv);
	}
}
