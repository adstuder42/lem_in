/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:55:01 by thzimmer          #+#    #+#             */
/*   Updated: 2019/02/20 11:45:37 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long long	ft_upow(unsigned long long nb, int pow)
{
	if (pow == 0)
		return (1);
	if (pow < 0)
		return (0);
	return (nb * ft_upow(nb, pow - 1));
}
