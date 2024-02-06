/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:15:48 by dklimkin          #+#    #+#             */
/*   Updated: 2023/09/04 22:15:49 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*su;
	unsigned char	cu;

	su = (unsigned char *)s;
	cu = (unsigned char)c;
	while (n--)
	{
		if (*su == cu)
			return (su);
		su++;
	}
	return (NULL);
}
