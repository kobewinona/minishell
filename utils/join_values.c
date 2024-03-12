/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:30 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/07 14:46:30 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_values(t_msh **msh, char **value, const char *s, size_t len)
{
	char	*temp1;
	char	*temp2;

	if (len <= 0)
		return (SUCCESS);
	temp1 = ft_substr(s, 0, len);
	if (!temp1)
		return (handle_err(msh, (t_err){T_SYS_ERR, MALLOC}, false), ERROR);
	temp2 = ft_strjoin((*value), temp1);
	free((*value));
	if (!temp2)
	{
		free(temp1);
		return (handle_err(msh, (t_err){T_SYS_ERR, MALLOC}, false), ERROR);
	}
	(*value) = temp2;
	free(temp1);
	return (SUCCESS);
}
