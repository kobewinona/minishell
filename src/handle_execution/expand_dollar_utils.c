/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:35:12 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/07 13:35:14 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_char_there(char *arg, char c)
{
	while (*arg)
	{
		if (*arg == c)
			return (true);
		arg++;
	}
	return (false);
}

char	*ft_strslice(const char *str, int start, int end)
{
	char	*slice;
	int		i;

	slice = (char *) malloc(sizeof(char) * (end - start + 1));
	if (slice == NULL)
		return (NULL);
	i = 0;
	while (str[i] && i < start)
		i++;
	while (str[i] && i < end)
	{
		slice[i - start] = str[i];
		i++;
	}
	slice[i] = '\0';
	return (slice);
}

int	ft_ind_char(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
