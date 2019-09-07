/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 09:32:22 by thzimmer          #+#    #+#             */
/*   Updated: 2018/11/10 14:45:36 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(char const *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char		*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	c;

	if (!str)
		return (NULL);
	j = 0;
	i = ft_strlen(str);
	c = 0;
	while (j < i - 1)
	{
		c = str[j];
		str[j] = str[i - 1];
		str[i - 1] = c;
		i--;
		j++;
	}
	return (str);
}
