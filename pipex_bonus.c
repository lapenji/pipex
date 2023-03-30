/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:47:44 by ltombell          #+#    #+#             */
/*   Updated: 2022/11/28 12:38:10 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	do_child(t_prg *prg, char *cmd, char **envp)
{
	int	pid;

	pipe(prg->pipa);
	pid = fork();
	if (pid == 0)
	{
		close(prg->pipa[0]);
		dup2(prg->pipa[1], 1);
		execute_cmd(cmd, envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(prg->pipa[1]);
		dup2(prg->pipa[0], 0);
	}
}

void	do_here_doc(t_prg *prg, char *delim)
{
	char	*linea;
	char	*delimiter;

	delimiter = ft_strjoin(delim, "\n");
	close(prg->pipa[0]);
	linea = get_next_line(0);
	while (linea)
	{
		if (!ft_strncmp(linea, delimiter, ft_strlen(delimiter) + 1))
		{
			close(1);
			free(linea);
			free(delimiter);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(linea, prg->pipa[1]);
		free(linea);
		linea = get_next_line(0);
	}
	close(1);
	free(linea);
	free(delimiter);
}

void	here_doc_handler(t_prg *prg, char *delim)
{
	int	pid;

	pipe(prg->pipa);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		close(prg->pipa[1]);
		dup2(prg->pipa[0], 0);
		close(prg->pipa[0]);
	}
	else
		do_here_doc(prg, delim);
}

void	ft_pipex(int argc, char **argv, char **envp)
{
	int		i;
	t_prg	prg;

	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		here_doc_handler(&prg, argv[2]);
		open_files(&prg, argv, 1, argc);
		i = 3;
	}
	else
	{
		open_files(&prg, argv, 2, argc);
		dup2(prg.infile, 0);
		i = 2;
	}
	while (i < argc - 2)
	{
		do_child(&prg, argv[i], envp);
		i++;
	}
	dup2(prg.of, 1);
	execute_cmd(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	if ((argc >= 5 && ft_strncmp(argv[1], "here_doc", 9)) || argc >= 6)
	{
		ft_pipex(argc, argv, envp);
	}
	else
		errors(2);
}
