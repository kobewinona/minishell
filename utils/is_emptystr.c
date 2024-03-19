/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_emptystr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:17:01 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/18 21:56:16 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_emptystr(const char *s)
{
	if (!s)
		return (false);
	while ((*s))
	{
		if (!ft_isspace((*s)))
			return (false);
		s++;
	}
	return (true);
}
