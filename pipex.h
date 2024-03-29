/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:17:31 by ltombell          #+#    #+#             */
/*   Updated: 2022/11/28 12:26:54 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_prg
{
	int		pipa[2];
	int		of;
	int		infile;
	int		pid;
}	t_prg;

char	**ft_split2(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
char	**get_paths(char **envp);
void	execute_cmd(char *cmd, char **envp);
void	errors(int tipo);
void	open_files(t_prg *prg, char **argv, int tipo, int argc);

#endif
