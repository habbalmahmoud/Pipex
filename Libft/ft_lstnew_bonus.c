/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:36:53 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/06 09:49:58 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list		*node;
	static int	i;

	i += 1;
	node = (t_list *)malloc(1 * sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->index = i - 1;
	node->next = NULL;
	return (node);
}
