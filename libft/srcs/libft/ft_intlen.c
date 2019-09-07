/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:50:52 by thzimmer          #+#    #+#             */
/*   Updated: 2019/04/29 18:50:53 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_intlen(int nb)
{
	int		len;

	len = 1;
	while ((nb = nb / 10))
		len++;
	return (len);
}