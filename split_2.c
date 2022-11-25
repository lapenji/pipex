/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:34:52 by ltombell          #+#    #+#             */
/*   Updated: 2022/11/25 18:22:26 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	countwords(char const *s, char c)
{
	int	count;
	int	i;
	int	flag;
	int	flag2;

	count = 0;
	i = 0;
	flag = 0;
	flag2 = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			return (count ++);
		if (s[i] != c && flag == 0 && flag2 == 0)
		{
			count++;
			flag = 1;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

static char	*create_word(char const *s, char c, int start)
{
	char	*newword;
	int		i;
	int		startcpy;

	i = 0;
	startcpy = start;
	while (s[start] != c && s[start] != '\0')
	{
		i++;
		start++;
	}
	newword = malloc (sizeof(char) * i + 1);
	i = 0;
	if (!newword)
		return (NULL);
	while (s[startcpy] != c && s[startcpy] != '\0')
	{
		newword[i] = s[startcpy];
		i++;
		startcpy++;
	}
	newword[i] = '\0';
	return (newword);
}

char	*create_word_virgo(char const *s, int start, char c)
{
	char	*newword;
	int		i;
	int		startcpy;

	i = 0;
	startcpy = start;
	start++;
	while (s[start] != c && s[start] != '\0')
	{
		i++;
		start++;
	}
	i++;
	newword = malloc (sizeof(char) * i + 1);
	i = 0;
	if (!newword)
		return (NULL);
	while (s[startcpy] != c && s[startcpy] != '\0')
	{
		newword[i] = s[startcpy];
		i++;
		startcpy++;
	}
	newword[i] = '\0';
	return (newword);
}

char	**ft_split2(char const *s, char c)
{
	char	**strarr;
	int		i;
	int		b;
	int		flag;

	strarr = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (!strarr)
		return (NULL);
	i = 0;
	b = 0;
	flag = 0;
	while (s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && flag == 0)
		{
			strarr[b] = create_word_virgo(s, i + 1, s[i]);
			strarr[b + 1] = 0;
			return (strarr);
		}
		else if (s[i] != c && flag == 0)
		{
			strarr[b] = create_word(s, c, i);
			b++;
			flag = 1;
		}
		if (s[i] == c)
			flag = 0;
		i++;
	}
	strarr[b] = NULL;
	return (strarr);
}
