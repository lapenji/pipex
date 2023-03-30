/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:25:25 by ltombell          #+#    #+#             */
/*   Updated: 2022/11/28 12:28:20 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_son(t_prg *data, char *cmd, char **envp)
{
	dup2 (data->pipa[1], 1);
	close(data->pipa[0]);
	dup2 (data->infile, 0);
	execute_cmd(cmd, envp);
}

void	ft_father(t_prg *data, char *cmd, char **envp)
{
	dup2 (data->pipa[0], 0);
	close(data->pipa[1]);
	dup2 (data->of, 1);
	execute_cmd(cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_prg	prg;

	if (argc == 5)
	{
		open_files(&prg, argv, 2, argc);
		pipe(prg.pipa);
		prg.pid = fork();
		if (prg.pid == 0)
			ft_son(&prg, argv[2], envp);
		else
			ft_father(&prg, argv[3], envp);
	}
	else
	{
		perror("wrong number of arguments");
		exit(EXIT_FAILURE);
	}
}
