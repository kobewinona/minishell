/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:25:01 by dklimkin          #+#    #+#             */
/*   Updated: 2023/08/28 16:25:02 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned char	*p_haystack;
	unsigned char	*p_needle;
	size_t			i;
	size_t			j;

	if (!*((unsigned char *)needle))
		return ((char *)haystack);
	p_haystack = (unsigned char *)haystack;
	p_needle = (unsigned char *)needle;
	i = 0;
	while (p_haystack[i] && i < len)
	{
		j = 0;
		while (p_haystack[i + j] == p_needle[j] && (i + j) < len)
		{
			j++;
			if (!p_needle[j])
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
