/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 23:19:10 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/23 10:47:04 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(char const *str)
{
	int					i;
	int					neg;
	unsigned long long	result;

	i = 0;
	neg = 1;
	result = 0;
	while (*str == ' ' || (*str > '\a' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (i >= 19 && result > 9223372036854775807)
		return (neg == -1 ? 0 : -1);
	return (result * neg);
}
