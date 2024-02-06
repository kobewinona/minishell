/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:19:27 by dklimkin          #+#    #+#             */
/*   Updated: 2023/08/30 12:19:28 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	total_len;

	if (s1 && s2)
		total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	else
		return (NULL);
	s3 = (char *)malloc(total_len * sizeof(char));
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, total_len);
	ft_strlcat(s3, s2, total_len);
	return (s3);
}
