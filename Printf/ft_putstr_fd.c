/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:03:28 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/02 09:31:43 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd_p(char *s, int fd, int *counter)
{
	int		i;

	i = 0;
	if (!s)
	{
		write (fd, "(null)", 6);
		*counter = *counter + 6;
	}
	else
	{
		while (s[i])
		{
			*counter = *counter + 1;
			write (fd, &s[i], 1);
			i++;
		}
	}
}

void	handle_strng(char *str, int *i, int *counter)
{
	ft_putstr_fd_p(str, 1, counter);
	*i = *i + 2;
}
