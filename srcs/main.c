/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:07:42 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/29 15:35:55 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/pipex.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void	process_one(int pipefd[2], char *infile)
{
	int	infile1;

	infile1 = open(infile, O_RDONLY);
	dup2(infile1, STDIN_FILENO);
	close (infile1);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	process_two(int pipefd[2], char *outfile)
{
	int	outfile1;

	outfile1 = open(outfile, O_RDWR | O_CREAT, 0777);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	dup2(outfile1, STDOUT_FILENO);
	close(outfile1);
}

void	close_and_wait(int pipefd[2], int pid, int pid2)
{
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	begin_pipe(char *path1, char *path2, char **av, char **env)
{
	int		pid;
	int		pid2;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit(ft_printf("Error\n"));
	pid = fork();
	if (pid == -1)
		exit(ft_printf("Error\n"));
	if (pid == 0)
	{
		process_one(pipefd, av[1]);
		execve(path1, ft_split(av[2], ' '), env);
	}
	pid2 = fork();
	if (pid2 == -1)
		exit(ft_printf("Error\n"));
	if (pid2 == 0)
	{
		process_two(pipefd, av[4]);
		execve(path2, ft_split(av[3], ' '), env);
	}
	close_and_wait(pipefd, pid, pid2);
}

int	main(int argc, char **argv, char **env)
{
	char	*path1;
	char	*path2;

	if (argc != 5)
		exit(ft_printf("Error\n"));
	if (access(argv[1], F_OK | R_OK) < 0)
		exit(ft_printf("Error\n"));
	if (access(argv[argc - 1], F_OK) == 0)
		if (access(argv[argc - 1], W_OK) < 0)
			exit(ft_printf("Error\n"));
	if (ft_strlen(argv[2]) < 1 || ft_strlen(argv[3]) < 1)
		exit(ft_printf("Error\n"));
	path1 = get_path(NULL, env, argv[2]);
	path2 = get_path(NULL, env, argv[3]);
	if (!path1 || !path2)
	{
		free(path2);
		free(path1);
		exit(ft_printf("Cmd Error\n"));
	}
	begin_pipe(path1, path2, argv, env);
	free(path1);
	free(path2);
}
