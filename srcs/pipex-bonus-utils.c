/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-bonus-utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:35:00 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/29 12:31:53 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/pipex.h"
#include <sys/wait.h>
#include <fcntl.h>

void	handle_doc(char *lim, int pipefd[2])
{
	char	*line;
	int		flag;

	flag = 1;
	close(pipefd[0]);
	while (flag)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, lim, ft_strlen(lim)) == 0)
		{
			free(line);
			flag -= flag;
			close(pipefd[1]);
			return ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
}

void	exec_command_(t_pipe popi, int argc, char **argv, char **env)
{
	int	i;

	i = 2;
	while (++i < argc - 1)
	{
		pipe(popi.pipefd);
		popi.pid = fork();
		if (popi.pid == -1)
			return ;
		else if (popi.pid == 0)
		{
			close(popi.pipefd[0]);
			exec_command(argv[i], popi.fd_in, popi.pipefd[1], env);
		}
		else
		{
			wait(NULL);
			close(popi.pipefd[1]);
			close(popi.fd_in);
			popi.fd_in = popi.pipefd[0];
		}
	}
}

void	handle_here_doc(int argc, char **argv, char **env)
{
	t_pipe	popi;

	pipe(popi.pipefd);
	popi.pid = fork();
	if (popi.pid == -1)
		return ;
	else if (popi.pid == 0)
	{
		handle_doc(argv[2], popi.pipefd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);
		popi.fd_in = popi.pipefd[0];
		close(popi.pipefd[1]);
		popi.outfile = open(argv[argc - 1], O_RDWR | O_CREAT, 0777);
		if (popi.outfile < 0)
		{
			close(popi.fd_in);
			exit(EXIT_FAILURE);
		}
		exec_command_(popi, argc, argv, env);
		exec_final_command(popi, env, argv, argc);
	}
}

char	*check_command(char **env, char **argv, int argc)
{
	int			i;
	int			j;
	int			flag;
	t_command	command;

	flag = 0;
	command.list_paths = split_paths(env, NULL);
	command.command = NULL;
	command.cmd = NULL;
	command.s_command = NULL;
	i = 1;
	while (++i < argc - 1)
	{
		j = -1;
		command.s_command = ft_strjoin("/", argv[i]);
		ext_for_check_command(command, &flag, j);
		if (flag == 0)
		{
			free_test(command.list_paths, command.s_command);
			exit(ft_printf("Error\n"));
		}
		free(command.s_command);
	}
	free_test(command.list_paths, NULL);
	return (NULL);
}

char	*check_commands(char **env, char **argv, int argc)
{
	int			i;
	int			j;
	int			flag;
	t_command	command;

	flag = 0;
	command.list_paths = split_paths(env, NULL);
	command.command = NULL;
	command.cmd = NULL;
	command.s_command = NULL;
	i = 2;
	while (++i < argc - 1)
	{
		j = -1;
		command.s_command = ft_strjoin("/", argv[i]);
		ext_for_check_command(command, &flag, j);
		if (flag == 0)
		{
			free_test(command.list_paths, command.s_command);
			exit(ft_printf("Error\n"));
		}
		free(command.s_command);
	}
	free_test(command.list_paths, NULL);
	return (NULL);
}
