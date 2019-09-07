/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:10:17 by thzimmer          #+#    #+#             */
/*   Updated: 2018/11/11 14:42:27 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	ft_wordlen(unsigned int index, char const *s, char c)
{
	unsigned int i;

	i = 0;
	while (s[index] && s[index] != c)
	{
		index++;
		i++;
	}
	return (i);
}

static unsigned int	ft_wordcount(char const *s, char c)
{
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = 0;
	while (s[i] && s[i] == c)
	{
		if (s[i + 1] == '\0')
			return (0);
		i++;
	}
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			n++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (n);
}

/*
** Create a table containing every sub sutrings separated by character c.
*/

char				**ft_strsplit(char const *s, char c)
{
	char			**tab;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	if (!s)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		while (s[i] && s[i] == c)
			i++;
		if (!(tab[j] = (char *)malloc(sizeof(char) * ft_wordlen(i, s, c) + 1)))
			return (NULL);
		while (s[i] && s[i] != c && ft_wordcount(s, c) > 0)
			tab[j][k++] = s[i++];
		tab[j][k] = '\0';
		j++;
	}
	tab[ft_wordcount(s, c)] = NULL;
	return (tab);
}
