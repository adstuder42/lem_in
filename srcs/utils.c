/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 10:55:08 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/23 10:55:21 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Repartit les fourmis dans l'ensemble des chemins de maniere optimale.
*/

static int	balanced_repartition(int **rep, int nbroutes)
{
	int		min;
	int		max;
	int		i[3];

	min = 2147483647;
	max = 0;
	i[2] = 0;
	i[1] = 0;
	i[0] = -1;
	while (++i[0] < nbroutes)
	{
		if ((*rep)[i[0]] < min && (i[1] = i[0]) >= 0)
			min = (*rep)[i[0]];
		if ((*rep)[i[0]] > max && (i[2] = i[0]) >= 0)
			max = (*rep)[i[0]];
	}
	if (max - min > 1)
	{
		(*rep)[i[1]]++;
		(*rep)[i[2]]--;
		return (balanced_repartition(rep, nbroutes));
	}
	return (1);
}

/*
** Deux cas :
** - mod = 1 donne un tableau avec le nombre de rounds pour chaque chemin.
** - mod = 0 donne un tableau avec le nombre de fourmis a envoyer par chemin.
*/

int			*repartition(int *routelen, int nbroutes, char mod)
{
	int		*rep;
	int		nb;
	int		i;

	if (!(rep = (int *)malloc(sizeof(int) * nbroutes)))
		return (NULL);
	i = -1;
	while (++i < nbroutes)
		rep[i] = g_nb.ants / nbroutes + routelen[i] - 1;
	nb = g_nb.ants % nbroutes;
	i = -1;
	while (++i < nb)
		rep[i]++;
	balanced_repartition(&rep, nbroutes);
	if (mod)
		return (rep);
	i = -1;
	while (++i < nbroutes)
		rep[i] -= (routelen[i] - 1);
	return (rep);
}

/*
** Calcule le nombre de tours pour faire parvenir toutes les fourmis a end.
*/

int			get_rounds(int *rep, int nbroutes)
{
	int	rounds;
	int	i;

	rounds = rep[0];
	i = -1;
	while (++i < nbroutes)
		if (rep[i] > rounds)
			rounds++;
	return (rounds);
}

/*
** Swappe les deux routeset et l'entier representant la longueur des routes.
*/

void		swap_routes(t_room *****routesets, int **routelen, int i[3])
{
	t_room	**route_buff;
	int		buff;

	buff = (*routelen)[i[1]];
	(*routelen)[i[1]] = (*routelen)[i[2]];
	(*routelen)[i[2]] = buff;
	route_buff = (*routesets)[i[0]][i[1]];
	(*routesets)[i[0]][i[1]] = (*routesets)[i[0]][i[2]];
	(*routesets)[i[0]][i[2]] = route_buff;
}

/*
** Teste un univers pour trouver d'eventuels doublons.
*/

char		doublon(t_room ****routes)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = -1;
	while ((*routes)[++i] && !(j = 0))
		while ((*routes)[i][++j + 1] && (k = i - 1) > -2)
			while ((*routes)[++k] && (l = i == k ? j : 0) > -1)
				while ((*routes)[k][++l + 1])
					if ((*routes)[i][j] == (*routes)[k][l])
					{
						g_nb.routes--;
						free((*routes)[i]);
						(*routes)[i] = NULL;
						return (1);
					}
	return (0);
}
