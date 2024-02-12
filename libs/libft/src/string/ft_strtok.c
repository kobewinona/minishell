/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:10:12 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/12 13:10:13 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

//static char	*get_tok(char **stash, const char *sep)
//{
//	char	*start;
//	char	*end;
//
//	start = *stash;
//	while (*start && ft_strchr(sep, *start))
//		*start++ = '\0';
//	if (*start == '\0')
//	{
//		*stash = start;
//		return (NULL);
//	}
//	end = start;
//	while (*end && !ft_strchr(sep, *end))
//		end++;
//	if (*end)
//	{
//		*end = '\0';
//		*stash = end + 1;
//	}
//	else
//		*stash = end;
//	return (start);
//}

static char	*get_tok(char **stash, const char *sep)
{
	char *start = *stash;
	char *end;
	int in_single_quote = 0, in_double_quote = 0;

	// Skip initial separators (unless they're within quotes)
	while (*start && ft_strchr(sep, *start) && !in_single_quote && !in_double_quote)
		start++;

	if (*start == '\0') {
		*stash = start;
		return (NULL);
	}

	end = start;
	while (*end) {
		if (*end == '\'' && !in_double_quote) {
			// Toggle single quote status if not within double quotes
			in_single_quote = !in_single_quote;
		} else if (*end == '\"' && !in_single_quote) {
			// Toggle double quote status if not within single quotes
			in_double_quote = !in_double_quote;
		} else if (!in_single_quote && !in_double_quote && ft_strchr(sep, *end)) {
			// If we're not in quotes and we hit a separator, stop
			break;
		}
		end++;
	}

	if (*end) {
		*end = '\0';
		*stash = end + 1;
	} else {
		*stash = end;
	}

	return start;
}

char	*ft_strtok(char *restrict str, const char *restrict sep)
{
	static char	*stash;

	if (str)
		stash = str;
	if (!stash || *stash == '\0')
		return (NULL);
	return (get_tok(&stash, sep));
}
