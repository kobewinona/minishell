/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:14:53 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/21 08:04:23 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_code(t_msh **msh, int encoded_exit_code)
{
	if (WIFSIGNALED(encoded_exit_code))
		(*msh)->exit_code = 128 + WTERMSIG(encoded_exit_code);
	if (WIFEXITED(encoded_exit_code))
		(*msh)->exit_code = WEXITSTATUS(encoded_exit_code);
}
