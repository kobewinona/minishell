/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:04:14 by dklimkin          #+#    #+#             */
/*   Updated: 2023/08/27 18:04:16 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = 0;
	src_len = 0;
	if (dst && src)
	{
		dst_len = ft_strlen(dst);
		src_len = ft_strlen(src);
	}
	if (dstsize > dst_len)
	{
		i = dst_len;
		while (i < (dstsize - 1) && *src)
		{
			dst[i] = *src;
			src++;
			i++;
		}
		dst[i] = '\0';
	}
	else
		return (src_len + dstsize);
	return (dst_len + src_len);
}
