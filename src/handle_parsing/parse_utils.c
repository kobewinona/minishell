/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:26:56 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/27 14:15:57 by dklimkin         ###   ########.fr       */
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
		return (print_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_int);
	temp2 = ft_strjoin((*value), temp1);
	free((*value));
	if (!temp2)
	{
		free(temp1);
		return (print_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_int);
	}
	(*value) = temp2;
	free(temp1);
	return (SUCCESS);
}

int	get_arb_fd(char **s)
{
	int	fd;
	int	i;

	i = (int)ft_strlen(*s) - 1;
	if ((*s) && !is_emptystr(*s))
	{
		while ((*s) && !ft_isspace((*s)[i]))
			i--;
		fd = ft_atoi(&(*s)[i]);
		if (fd > 0)
			(*s)[i] = '\0';
		else
			fd = UNSPECIFIED;
	}
	return (fd);
}

int	populate_argv(t_msh **msh, char **argv, char *input)
{
	int		index;

	if (!input)
		return (ERROR);
	index = 0;
	while (argv && argv[index])
		index++;
	while (!is_emptystr(input))
	{
		argv[index] = get_value(msh, &input);
		if (!argv[index])
			return (ERROR);
		if (!argv[index])
			return (print_err(msh, (t_err){T_SYS_ERR, MALLOC}, false).t_int);
		index++;
	}
	return (SUCCESS);
}
