/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:46:51 by dklimkin          #+#    #+#             */
/*   Updated: 2023/08/31 16:46:52 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*modified_s;
	size_t	i;

	modified_s = NULL;
	if (s && f)
	{
		modified_s = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
		if (!modified_s)
			return (NULL);
		i = 0;
		while (s[i])
		{
			modified_s[i] = f(i, s[i]);
			i++;
		}
		modified_s[i] = '\0';
	}
	return (modified_s);
}
