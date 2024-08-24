/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:43:18 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/02 11:03:02 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, int (*f)(int), void (*del)(int))
{
	int		content;
	t_list	*new_node;
	t_list	*new_list;

	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
			ft_lstdelone(new_node, del);
		else
			ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
