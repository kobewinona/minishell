/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:51:35 by dklimkin          #+#    #+#             */
/*   Updated: 2023/08/30 11:51:36 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	s_len;
	size_t	sub_s_len;
	size_t	i;

	if (s)
	{
		s_len = ft_strlen(s);
		sub_s_len = s_len - start;
	}
	if (!s || start > s_len)
		len = 0;
	else
		sub_s_len = s_len - start;
	if (len > sub_s_len)
		len = sub_s_len;
	sub_s = (char *)malloc((len + 1) * sizeof(char));
	if (!sub_s)
		return (NULL);
	i = 0;
	while (i < len && s[start])
		sub_s[i++] = s[start++];
	sub_s[i] = '\0';
	return (sub_s);
}
