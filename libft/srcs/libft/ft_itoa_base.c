/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 12:20:42 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/23 10:47:44 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static long long	ft_pow(int n, int p)
{
	if (p == 0)
		return (1);
	if (p < 0)
		return (0);
	return (n * ft_pow(n, p - 1));
}

char				*ft_itoa_base(int n, int base)
{
	long long	nb;
	int			i;
	int			neg;
	char		*result;

	nb = n;
	if (!(neg = 0) && nb < 0)
	{
		base == 10 ? neg = 1 : 0;
		nb = -nb;
	}
	i = 1;
	while (ft_pow(base, i) - 1 < nb)
		i++;
	if (base < 2 || !(result = (char *)malloc(sizeof(char) * (i + 1 + neg))))
		return (NULL);
	result[i + neg] = '\0';
	if (neg)
		result[0] = '-';
	while (i-- > 0)
	{
		result[i + neg] = nb % base + (nb % base > 9 ? 'A' - 10 : '0');
		nb = nb / base;
	}
	return (result);
}
