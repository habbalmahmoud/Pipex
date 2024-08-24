/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:01:41 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/04 22:21:58 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(int))
{
	t_list	*list;
	t_list	*temp;

	if (!*lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		temp = list->next;
		ft_lstdelone(list, del);
		list = temp;
	}
	*lst = NULL;
	free(temp);
}
