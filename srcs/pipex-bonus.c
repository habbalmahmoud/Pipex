/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:14:49 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/29 12:54:52 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/pipex.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/wait.h"

void	exec_final_command(t_pipe pipo, char **env, char **argv, int argc)
{
	if (pipo.fd_in != 0)
	{
		dup2(pipo.fd_in, 0);
		close(pipo.fd_in);
	}
	if (pipo.outfile != 1)
	{
		dup2(pipo.outfile, 1);
		close(pipo.outfile);
	}
	execve(get_path(NULL, env, argv[argc - 2]),
		ft_split(argv[argc - 2], ' '), NULL);
}

void	exec_command(char *cmd, int infile, int outfile, char **env)
{
	char	*command;

	if (infile != 0)
	{
		dup2 (infile, 0);
		close(infile);
	}
	if (outfile != 1)
	{
		dup2 (outfile, 1);
		close(outfile);
	}
	command = get_path(NULL, env, cmd);
	execve(command, ft_split(cmd, ' '), NULL);
}

void	do_the_work(char **argv, char **env, t_pipe pipo, int argc)
{
	int	i;

	i = 1;
	while (++i < argc - 2)
	{
		pipe(pipo.pipefd);
		pipo.pid = fork();
		if (pipo.pid == -1)
			return ;
		else if (pipo.pid == 0)
		{
			close(pipo.pipefd[0]);
			exec_command(argv[i], pipo.fd_in, pipo.pipefd[1], env);
		}
		else
		{
			wait(NULL);
			close(pipo.pipefd[1]);
			close(pipo.fd_in);
			pipo.fd_in = pipo.pipefd[0];
		}
	}
}

void	execute_pipes(char **env, int argc, char **argv)
{
	t_pipe	pipo;

	pipo.infile = open(argv[1], O_RDONLY);
	if (!pipo.infile)
		return ;
	pipo.outfile = open(argv[argc - 1], O_RDWR | O_CREAT, 0777);
	if (!pipo.outfile)
		return ;
	pipo.fd_in = pipo.infile;
	do_the_work(argv, env, pipo, argc);
	exec_final_command(pipo, env, argv, argc);
}

int	main(int argc, char **argv, char **env)
{
	if (argc < 4)
		exit(ft_printf("Error\n"));
	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
	{
		if (access(argv[1], F_OK | W_OK) < 0)
			exit(ft_printf("Error\n"));
		if (access(argv[argc - 1], F_OK) == 0)
			if (access(argv[argc - 1], W_OK) < 0)
				exit(ft_printf("Error\n"));
		check_empty(argv);
		check_command(env, argv, argc);
		execute_pipes(env, argc, argv);
	}
	else if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			exit(ft_printf("Error\n"));
		if (access(argv[argc - 1], F_OK) == 0)
			if (access(argv[argc - 1], W_OK) < 0)
				exit(ft_printf("Error\n"));
		check_empty_(argv);
		check_commands(env, argv, argc);
		handle_here_doc(argc, argv, env);
	}
}
