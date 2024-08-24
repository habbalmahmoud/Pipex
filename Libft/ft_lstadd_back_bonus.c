/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:31:39 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/05 00:44:39 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		(*lst) = new;
		return ;
	}
	while (temp)
	{
		if (temp->next == NULL)
		{
			temp->next = new;
			return ;
		}
		temp = temp->next;
	}
}
