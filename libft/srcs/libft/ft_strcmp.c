/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 23:18:39 by thzimmer          #+#    #+#             */
/*   Updated: 2019/02/20 13:45:04 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(char const *s1, char const *s2)
{
	int				i;
	unsigned char	*p1;
	unsigned char	*p2;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	i = -1;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (p1[++i] || p2[i])
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
	return (0);
}
