/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:10:12 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/12 13:10:13 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	*get_tok(char **stash, const char *sep)
{
	char	*start;
	char	*end;

	start = *stash;
	while (*start && ft_strchr(sep, *start))
	{
		*start = '\0';
		start++;
	}
	if (*start == '\0')
	{
		*stash = start;
		return (NULL);
	}
	end = start;
	while (*end && !ft_strchr(sep, *end))
		end++;
	if (*end)
	{
		*end = '\0';
		*stash = end + 1;
	}
	else
		*stash = end;
	return (start);
}

char	*ft_strtok(char *restrict str, const char *restrict sep)
{
	static char	*stash;

	if (str)
		stash = str;
	if (!stash || *stash == '\0')
		return (NULL);
	return (get_tok(&stash, sep));
}
