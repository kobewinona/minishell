/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:12:58 by dklimkin          #+#    #+#             */
/*   Updated: 2023/08/30 13:13:00 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char_in_set(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1);
	while (is_char_in_set(s1[start], set))
		start++;
	while (start < end && is_char_in_set(s1[end - 1], set))
		end--;
	s2 = (char *)ft_calloc((end - start) + 1, sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, (s1 + start), (end - start) + 1);
	return (s2);
}
