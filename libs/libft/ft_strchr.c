/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:39:14 by dklimkin          #+#    #+#             */
/*   Updated: 2023/08/27 20:39:15 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	cu;

	cu = (unsigned char)c;
	while (*s)
	{
		if (*s == cu)
			return ((char *)s);
		s++;
	}
	if (cu == '\0')
		return ((char *)s);
	return (NULL);
}
