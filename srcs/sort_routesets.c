/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_routesets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:23:12 by thzimmer          #+#    #+#             */
/*   Updated: 2019/05/08 17:03:16 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Swappe les deux univers de set pour avoir le meilleur a l'index 0.
*/

static char	swap_routesets(t_room *****routesets, int i, int rounds)
{
	t_room	***routesetbuff;
	int		*routelen;
	int		*rep2;
	int		nbroutes;
	int		rounds2;

	rep2 = NULL;
	if (!(routelen = get_routelen((*routesets)[i])))
		return (0);
	nbroutes = 0;
	while ((*routesets)[i][nbroutes])
		nbroutes++;
	if (!(rep2 = repartition(routelen, nbroutes, 1)))
		return (0);
	free(routelen);
	rounds2 = get_rounds(rep2, nbroutes);
	free(rep2);
	if (rounds >= rounds2)
	{
		routesetbuff = (*routesets)[0];
		(*routesets)[0] = (*routesets)[i];
		(*routesets)[i] = routesetbuff;
		return (1);
	}
	return (1);
}

/*
** Choisis le routeset adapte au probleme.
*/

static char	select_routeset(t_room *****routesets)
{
	int		*routelen;
	int		*rep;
	int		nbroutes;
	int		rounds;
	int		i;

	i = 0;
	while (++i < g_nb.routes && !(nbroutes = 0))
	{
		if (!(routelen = get_routelen((*routesets)[0])))
			return (0);
		while ((*routesets)[0][nbroutes])
			nbroutes++;
		if (!(rep = repartition(routelen, nbroutes, 1)))
			return (0);
		free(routelen);
		rounds = get_rounds(rep, nbroutes);
		free(rep);
		if (!swap_routesets(routesets, i, rounds))
			return (0);
	}
	return (1);
}

/*
** Trie les routesets pour avoir la route la plus courte au debut.
*/

char		sort_routesets(t_room *****routesets)
{
	int		*routelen;
	int		i[3];

	routelen = NULL;
	i[0] = -1;
	while ((*routesets)[++i[0]] && (i[1] = -1))
	{
		if (!(routelen = get_routelen((*routesets)[i[0]])))
			return (0);
		while ((*routesets)[i[0]][++i[1]] && (i[2] = i[1]) >= 0)
			while ((*routesets)[i[0]][++i[2]])
				if (routelen[i[1]] - routelen[i[2]] > 0)
					swap_routes(routesets, &routelen, i);
		free(routelen);
	}
	if (!select_routeset(routesets))
		return (0);
	return (1);
}
