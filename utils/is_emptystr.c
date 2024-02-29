/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_emptystr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:17:01 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/13 22:24:26 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_emptystr(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (false);
	while (s[i])
	{
		if (!ft_isspace(s[i]) || s[i] != 73)
			return (false);
		i++;
	}
	return (true);
}
