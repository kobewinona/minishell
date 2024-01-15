/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:01:35 by dklimkin          #+#    #+#             */
/*   Updated: 2023/09/04 22:01:36 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		s_len;
	long	temp_n;

	temp_n = (long)n;
	s_len = count_digits(temp_n);
	s = (char *)malloc((s_len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[s_len] = '\0';
	if (temp_n == 0)
		s[0] = '0';
	if (temp_n < 0)
	{
		s[0] = '-';
		temp_n *= -1;
	}
	while (temp_n > 0)
	{
		s[--s_len] = (temp_n % 10) + '0';
		temp_n /= 10;
	}
	return (s);
}
