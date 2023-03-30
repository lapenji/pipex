/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:48:53 by ltombell          #+#    #+#             */
/*   Updated: 2022/11/28 12:31:22 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "get_next_line.h"
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
}	t_prg;

char	**ft_split2(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putstr_fd(char *s, int fd);
void	errors(int tipo);
void	open_files(t_prg *prg, char **argv, int tipo, int argc);
char	**get_paths(char **envp);
void	free_arrays_n_error(char **arr, char **arr2);
void	execute_cmd(char *cmd, char **envp);

#endif
