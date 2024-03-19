/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_exit_code.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:14:53 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/20 03:12:08 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	collect_exit_code(t_msh **msh, int ext_code_encoded)
{
	if (WIFEXITED(ext_code_encoded))
		(*msh)->exit_code = WEXITSTATUS(ext_code_encoded);
	else if (WIFSIGNALED(ext_code_encoded))
		(*msh)->exit_code = 128 + WTERMSIG(ext_code_encoded);
}
