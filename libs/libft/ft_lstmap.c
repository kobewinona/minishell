/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 22:10:26 by dklimkin          #+#    #+#             */
/*   Updated: 2023/09/05 22:10:29 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_current;
	void	*content;

	new_head = NULL;
	while (lst && f && del)
	{
		content = f(lst->content);
		new_current = ft_lstnew(content);
		if (!new_current)
		{
			del(content);
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		ft_lstadd_back(&new_head, new_current);
		lst = lst->next;
	}
	return (new_head);
}
