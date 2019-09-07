/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_augmenting_paths.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 10:49:16 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/27 15:37:24 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Initialise augmenting_path, la queue et le premier univers avec la 1st route.
** La queue contiendra uniquement la salle start.
** - ap : augmenting_path
** - q  : queue
** - rs : routesets
** - fr : first_route
*/

static char	init_rs(t_room ***ap, t_room ***q, t_room *****rs, t_room ***fr)
{
	if (!(*rs = (t_room ****)malloc(sizeof(t_room ***) * 2)))
		return (0);
	if (!((*rs)[0] = (t_room ***)malloc(sizeof(t_room **) * 2)))
		return (0);
	(*rs)[0][0] = *fr;
	(*rs)[0][1] = NULL;
	(*rs)[1] = NULL;
	if (!(*q = (t_room **)malloc(sizeof(t_room *) * (g_nb.rooms * 2 + 1))))
		return (0);
	(*q)[0] = (*fr)[0];
	(*q)[1] = NULL;
	if (!(*ap = (t_room **)malloc(sizeof(t_room *) * (g_nb.rooms + 1))))
		return (0);
	(*ap)[0] = NULL;
	(*ap)[1] = NULL;
	return (1);
}

/*
** Condition lors d'une visite de salle appartenant a une route existante.
*/

static char	visit_route(t_room ***queue, int i, int j, int *mark)
{
	t_room	*visited;
	int		k;

	visited = (*queue)[i]->link[j];
	if (!(k = 0) && !(*queue)[i]->flow[j] && !visited->type \
		&& ((*queue)[i]->dist < visited->dist - 1 || !visited->dist))
	{
		while (visited->link[k] && visited->flow[k] != -1)
			k++;
		if (visited->flow[k] == -1 && visited->link[k]->type != 2 \
			&& (!visited->link[k]->dist \
				|| (*queue)[i]->dist - 1 <= visited->link[k]->dist))
		{
			visited->from = (*queue)[i];
			visited->dist = (*queue)[i]->dist + 1;
			visited->link[k]->from = visited;
			visited->link[k]->dist = visited->dist - 1;
			(*queue)[*mark] = visited->link[k];
			(*queue)[++(*mark)] = NULL;
		}
		return (1);
	}
	return (0);
}

/*
** Visite la salle et l'ajoute a la queue si sa distance est raccourcie.
*/

static char	visit_room(t_room ***queue, int i, int j, int *mark)
{
	t_room	*visited;

	visited = (*queue)[i]->link[j];
	if (!(*queue)[i]->flow[j] && visited->type \
		&& ((*queue)[i]->dist < visited->dist - 1 || !visited->dist))
	{
		visited->from = (*queue)[i];
		visited->dist = (*queue)[i]->dist + 1;
		(*queue)[*mark] = visited;
		(*queue)[++(*mark)] = NULL;
		return (1);
	}
	if (visit_route(queue, i, j, mark))
		return (1);
	if ((*queue)[i]->flow[j] == -1 && ((*queue)[i]->dist - 1 \
			<= visited->dist || !visited->dist))
		return (0);
	return (1);
}

/*
** Initialise la queue en y inserant la premiere salle. Parcours ensuite le
** graphe a la recherche de la route permettant un ensemble plus court.
*/

char		bfs(t_room ***queue)
{
	int	mark;
	int	end;
	int	i;
	int	j;

	mark = 1;
	i = -1;
	end = 0;
	while (mark < g_nb.rooms * 2 && (*queue)[++i] && (j = -1))
		if ((*queue)[i]->type != 3 || !(end = 1))
			while (mark < g_nb.rooms * 2 && (*queue)[i]->link[++j])
				if ((*queue)[i]->link[j]->type != 2 \
					&& !visit_room(queue, i, j, &mark))
				{
					(*queue)[i]->link[j]->from = (*queue)[i];
					(*queue)[i]->link[j]->dist = (*queue)[i]->dist - 1;
					(*queue)[mark] = (*queue)[i]->link[j];
					(*queue)[++mark] = NULL;
				}
	return (end && cycle_detection(queue) ? 1 : 0);
}

/*
** Algorithme qui itere pour trouver les univers de routes contenant une route
** supplementaire.
*/

t_room		****find_augmenting_paths(t_room ***first_route, t_room *start)
{
	t_room	****routesets;
	t_room	***routes;
	t_room	**aug_path;
	t_room	**queue;
	int		i;

	if ((i = 0) || !(init_rs(&aug_path, &queue, &routesets, first_route)))
		return (NULL);
	while ((bfs(&queue)))
	{
		mark_flows(&aug_path, start, start->next);
		if (!(read_flows(start, &routes)) \
			|| !realloc_rs(&routesets, routes, ++i))
		{
			free_routesets(&routesets);
			free(aug_path);
			free(queue);
			return (NULL);
		}
		if (doublon(&routesets[i]))
			break ;
	}
	free(aug_path);
	free(queue);
	return (!sort_routesets(&routesets) ? NULL : routesets);
}
