/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinmulti.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:51:40 by thzimmer          #+#    #+#             */
/*   Updated: 2019/04/29 18:51:43 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdarg.h>

/*
** Create a new string containig the nb following strings.
*/

char		*ft_strjoinmulti(int nb, ...)
{
	va_list	ap;
	char	**tab;
	char	*tmp;
	char	*res;
	int		i;

	if (nb < 2 || !(tab = (char **)malloc(sizeof(char *) * (nb + 1))))
		return (NULL);
	va_start(ap, nb);
	i = -1;
	while (++i < nb)
		tab[i] = va_arg(ap, char *);
	tab[i] = NULL;
	va_end(ap);
	i = 0;
	res = ft_strdup(tab[0]);
	while (tab[++i])
	{
		tmp = ft_strjoin(res, tab[i]);
		free(res);
		res = tmp;
	}
	free(tab);
	return (res);
}
