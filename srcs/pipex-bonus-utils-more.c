/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-bonus-utils-more.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:20:19 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/29 12:58:44 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/pipex.h"

void	free_test(char **str, char *str1)
{
	free_2d_arrays(str, NULL);
	free(str1);
}

void	ext_for_check_command(t_command command, int *flag, int j)
{
	while (command.list_paths[++j])
	{
		command.command = ft_split(command.s_command, ' ');
		command.cmd = ft_strjoin(command.list_paths[j], command.command[0]);
		if (access(command.cmd, F_OK | X_OK) == 0)
			*flag += 1;
		free_test(command.command, command.cmd);
	}
}

void	check_empty(char **argv)
{
	int	i;

	i = 1;
	while (argv[++i])
	{
		if (ft_strlen(argv[i]) < 1)
			exit(ft_printf("Error\n"));
	}
}

void	check_empty_(char **argv)
{
	int	i;

	i = 2;
	while (argv[++i])
	{
		if (ft_strlen(argv[i]) < 1)
			exit(ft_printf("Error\n"));
	}
}
