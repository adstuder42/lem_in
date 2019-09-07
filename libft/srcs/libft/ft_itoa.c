/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 20:08:18 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/23 10:46:44 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa(int n)
{
	long long	nb;
	int			i;
	int			neg;
	char		*result;

	nb = n;
	if (!(neg = 0) && nb < 0)
	{
		neg = 1;
		nb = -nb;
	}
	i = 1;
	while ((n = n / 10))
		i++;
	if (!(result = (char *)malloc(sizeof(char) * (i + neg) + 1)))
		return (NULL);
	result[i + neg] = '\0';
	if (neg)
		result[0] = '-';
	while (i-- > 0)
	{
		result[i + neg] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (result);
}
