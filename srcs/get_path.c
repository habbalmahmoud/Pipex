/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:28:33 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/23 15:15:37 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/pipex.h"

void	free_2d_arrays(char **str, char **str2)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
	i = 0;
	if (str2)
	{
		while (str2[i])
		{
			free(str2[i]);
			i++;
		}
		free(str2);
	}
}

char	**split_paths(char **env, char *start)
{
	int		i;
	char	**list_paths;

	list_paths = NULL;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			start = ft_substr(env[i], 5, ft_strlen(env[i]));
			list_paths = ft_split(start, ':');
			free(start);
		}
	}
	return (list_paths);
}

char	*get_path(char	*str, char **env, char *cmd)
{
	char	**list_paths;
	char	**command;
	int		i;
	char	*start;

	start = NULL;
	list_paths = NULL;
	list_paths = split_paths(env, start);
	i = -1;
	command = ft_split(cmd, ' ');
	cmd = ft_strjoin("/", command[0]);
	while (list_paths[++i])
	{
		str = ft_strjoin(list_paths[i], cmd);
		if (access(str, F_OK | X_OK) == 0)
		{
			free(cmd);
			free_2d_arrays(command, list_paths);
			return (str);
		}
		free(str);
	}
	free_2d_arrays(list_paths, command);
	return (free(cmd), NULL);
}
