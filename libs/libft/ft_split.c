/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:25:09 by dklimkin          #+#    #+#             */
/*   Updated: 2023/08/30 16:25:10 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_sub_s(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static void	handle_malloc_error(char **arr)
{
	size_t	index;

	index = 0;
	while (arr[index])
	{
		free(arr[index]);
		index++;
	}
	free(arr);
}

static char	**handle_s_split(char **arr, char const *s, char c)
{
	size_t	sub_s_len;
	size_t	index;

	index = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			sub_s_len = 0;
			while (s[sub_s_len] && s[sub_s_len] != c)
				sub_s_len++;
			arr[index] = ft_substr(s, 0, sub_s_len);
			if (!arr[index])
			{
				handle_malloc_error(arr);
				return (NULL);
			}
			s += sub_s_len;
			index += 1;
		}
	}
	arr[index] = (NULL);
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = (char **)malloc((count_sub_s(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (handle_s_split(arr, s, c));
}
