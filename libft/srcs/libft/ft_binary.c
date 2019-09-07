/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 12:20:42 by thzimmer          #+#    #+#             */
/*   Updated: 2019/02/20 11:44:32 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int			ft_strlen(char *str)
{
	int				i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static long double	ft_dpow(long double nb, int pow)
{
	if (pow == 0)
		return (1);
	if (pow < 0)
		return (0);
	return (nb * ft_dpow(nb, pow - 1));
}

static char			*ft_strrev(char *str)
{
	int				i;
	int				j;
	char			c;

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

/*
**	Converts the number n represented in long double in a string of binary char.
*/

char				*ft_binary(long double n)
{
	int				i;
	int				j;
	long double		buff;
	char			*result;

	i = 1;
	while (ft_dpow(2.L, i) <= n)
		i++;
	if (!(result = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	result[i] = '\0';
	while (i-- > 0 && !(j = 0))
	{
		buff = n;
		while (buff - ft_dpow(2.L, i) >= 0.L)
		{
			buff = buff - ft_dpow(2.L, i);
			j++;
		}
		n = n - j * ft_dpow(2.L, i);
		result[i] = j + '0';
	}
	return ((result = ft_strrev(result)));
}
