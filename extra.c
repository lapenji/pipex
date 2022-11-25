/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:09:10 by ltombell          #+#    #+#             */
/*   Updated: 2022/11/25 18:38:46 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	errors(int tipo)
{
	if (tipo == 1)
		write(2, "Error:\nunable to open infile\n", 30);
	else if (tipo == 2)
		write(2, "Error:\nwrong number of arguments\n", 33);
	else if (tipo == 2)
		write(2, "Error:\noutfile problem\n", 23);
	exit(EXIT_FAILURE);
}

void	open_files(t_prg *prg, char **argv, int tipo, int argc)
{
	if (tipo == 1)
	{
		prg->of = open(argv[argc - 1], O_APPEND | O_CREAT | O_RDWR, 0000644);
		if (prg->of < 0)
			errors(3);
	}
	else if (tipo == 2)
	{
		prg->of = open(argv[argc -1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (prg->of == -1)
			errors(3);
		prg->infile = open(argv[1], O_RDONLY);
		if (prg->infile == -1)
			errors(1);
	}
}

char	**get_paths(char **envp)
{
	int		i;
	char	*tmp;
	char	**res;

	i = 0;
	while (envp[i][0] != 'P' || envp[i][1] != 'A' || envp[i][2] != 'T')
	{
		i++;
	}
	tmp = ft_strtrim(envp[i], "PATH=");
	res = ft_split2(tmp, ':');
	free(tmp);
	return (res);
}

void	free_arrays_n_error(char **arr, char **arr2)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	i = 0;
	while (arr2[i] != 0)
	{
		free(arr2[i]);
		i++;
	}
	free(arr2);
	perror("command not found");
	exit(127);
}

void	execute_cmd(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	**cmd_args;
	char	**cmd_paths;

	i = 0;
	cmd_args = ft_split2(cmd, ' ');
	if (access(cmd, F_OK) == 0)
		execve(cmd, cmd_args, envp);
	cmd_paths = get_paths(envp);
	while (cmd_paths[i] != 0)
	{
		tmp = ft_strjoin(cmd_paths[i], "/");
		free(cmd_paths[i]);
		cmd_paths[i] = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (access(cmd_paths[i], F_OK) == 0)
			break ;
		i++;
	}
	if (cmd_paths[i] == 0)
		free_arrays_n_error(cmd_paths, cmd_args);
	if (execve(cmd_paths[i], cmd_args, envp) == -1)
		free_arrays_n_error(cmd_paths, cmd_args);
}
