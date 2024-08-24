/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:42:17 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/04 16:38:47 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../Printf/ft_printf.h"
#include <stdlib.h>

void	check_val(long num)
{
	if (num > 2147483647 || num < -2147483648)
	{
		ft_printf("Error\n");
		exit(0);
	}
}

int	ft_atoi(char *str)
{
	long	num;
	int		i;
	int		prod;

	prod = 1;
	i = 0;
	num = 0;
	while ((str[i] >= 7 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		prod = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	check_val(num * prod);
	return (num * prod);
}
