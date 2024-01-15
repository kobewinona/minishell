/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:02:16 by dklimkin          #+#    #+#             */
/*   Updated: 2023/08/27 21:02:18 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	cu;
	size_t			s_len;

	cu = (unsigned char)c;
	s_len = ft_strlen(s);
	if (cu == '\0')
		return ((char *)(s + s_len));
	while (s_len--)
	{
		if (s[s_len] == cu)
			return ((char *)(s + s_len));
	}
	return (NULL);
}
