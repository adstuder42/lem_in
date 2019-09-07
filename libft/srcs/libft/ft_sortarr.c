/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortarr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 23:19:10 by thzimmer          #+#    #+#             */
/*   Updated: 2019/04/29 18:51:30 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		ft_sortarr(int **numbers, int len)
{
	int		i;
	int		j;
	int		buff;

	i = -1;
	while (++i < len && ((j = i) + 1))
		while (++j < len)
			if ((*numbers)[i] > (*numbers)[j])
			{
				buff = (*numbers)[i];
				(*numbers)[i] = (*numbers)[j];
				(*numbers)[j] = buff;
			}
}
