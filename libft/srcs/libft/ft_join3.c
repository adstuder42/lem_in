/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:25:32 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/23 13:27:43 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(char const *s)
{
	int		len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

/*
** Create a new string from 3 strings and stores it in s1.
** Previous content is freed.
** -NOTE : Caller must have malloc'd s1 or initalized it to NULL.
*/

void		ft_join3(char **s1, char const *s2, char const *s3)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = ft_strlen(*s1);
	j = ft_strlen(s2);
	k = ft_strlen(s3);
	if (!(new = (char *)malloc(sizeof(char) * (i + j + k + 1))))
		return ;
	new[i + j + k] = '\0';
	while (--k >= 0)
		new[i + j + k] = s3[k];
	while (--j >= 0)
		new[i + j] = s2[j];
	while (--i >= 0)
		new[i] = (*s1)[i];
	free(*s1);
	*s1 = new;
}
