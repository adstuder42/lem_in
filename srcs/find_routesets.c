/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_routesets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:06:55 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/23 10:51:26 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Initialise la queue pour contenir autant de salles que le nombre total
** de salles dans la map et initialise les tableaux de flux dans les salles.
*/

static char	init_lem_in(t_room *start, t_room ***queue)
{
	int	i;
	int	len;

	g_nb.routes = 1;
	if (!(*queue = (t_room **)malloc(sizeof(t_room *) * (g_nb.rooms + 1))))
		return (0);
	(*queue)[0] = start;
	(*queue)[1] = NULL;
	start->from = NULL;
	while (start)
	{
		len = start->nblinks;
		if (!(start->flow = (char *)malloc(sizeof(char) * (len + 1))))
			return (0);
		i = -1;
		while (++i < len)
			start->flow[i] = 0;
		start->dist = 0;
		start = start->next;
	}
	return (1);
}

/*
** Recupere les coordonnees de la salle.
*/

char		get_coords(t_room **room, char *line)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	(*room)->coord[0] = ft_atoi(&(line[++i]));
	while (line[i] != ' ')
		i++;
	(*room)->coord[1] = ft_atoi(&(line[++i]));
	return (1);
}

/*
** Initialise les routes pour en contenir <g_nb.routes>.
*/

char		init_routes(t_room ****routes)
{
	int	i;

	if (!(*routes = (t_room ***)malloc(sizeof(t_room **) * (g_nb.routes + 1))))
		return (0);
	i = -1;
	while (++i < g_nb.routes)
		if (!((*routes)[i] = (t_room **)malloc(sizeof(t_room *) \
			* (g_nb.rooms + 1))))
			return (0);
	(*routes)[g_nb.routes] = NULL;
	return (1);
}

/*
** Copie le tableau de routesets et y ajoute le nouveau set.
*/

char		realloc_rs(t_room *****routesets, t_room ***routes, int len)
{
	t_room	****newrs;
	int		i;

	if (!(newrs = (t_room ****)malloc(sizeof(t_room *) * (len + 2))))
		return (0);
	newrs[len] = routes;
	newrs[len + 1] = NULL;
	i = -1;
	while (++i < len)
		newrs[i] = (*routesets)[i];
	free(*routesets);
	*routesets = newrs;
	return (1);
}

/*
** Parcours le graphe avec un BFS a la recherche de la route la plus courte.
** Recherche ensuite un set de chemins les plus courts possibles a l'aide d'un
** l'algorithme de gestion de flux.
*/

t_room		****find_routesets(t_room *start)
{
	t_room	****routesets;
	t_room	**route;
	t_room	**queue;

	route = NULL;
	queue = NULL;
	if (!(route = (t_room **)malloc(sizeof(t_room *) * (g_nb.rooms + 1))) \
		|| !init_lem_in(start, &queue) || !bfs(&queue))
	{
		free(route);
		free(queue);
		return (NULL);
	}
	free(queue);
	mark_flows(&route, start, start->next);
	return ((routesets = find_augmenting_paths(&route, start)));
}
