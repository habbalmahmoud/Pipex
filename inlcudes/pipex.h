/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:02:00 by mhabbal           #+#    #+#             */
/*   Updated: 2024/07/29 12:39:48 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../Libft/libft.h"
# include "../Printf/ft_printf.h"
# include "../GNL/get_next_line.h"

typedef struct s_pipe
{
	int	pid;
	int	pipefd[2];
	int	infile;
	int	outfile;
	int	fd_in;
}	t_pipe;

typedef struct s_command
{
	char	**list_paths;
	char	**command;
	char	*cmd;
	char	*s_command;
}	t_command;

char		*get_path(char	*str, char **env, char *cmd);
void		free_2d_arrays(char **str, char **str2);
void		handle_here_doc(int argc, char **argv, char **env);
void		exec_command(char *cmd, int infile, int outfile, char **env);
void		exec_final_command(t_pipe pipo, char **env, char **argv, int argc);
char		**split_paths(char **env, char *start);
char		*check_commands(char **env, char **argv, int argc);
char		*check_command(char **env, char **argv, int argc);
void		free_test(char **str, char *str1);
void		ext_for_check_command(t_command command, int *flag, int j);
void		check_empty(char **argv);
void		check_empty_(char **argv);

#endif