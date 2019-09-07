/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flows_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:23:12 by thzimmer          #+#    #+#             */
/*   Updated: 2019/05/08 17:03:16 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Remonte et ecris la route a l'aide du pointeuri 'from' defini dans la salle.
*/

static void	write_route(t_room ***route, t_room *end)
{
	t_room	*cur;
	int		len;

	cur = end;
	len = 0;
	while (cur && ++len)
		cur = cur->from;
	(*route)[len] = NULL;
	while (end)
	{
		(*route)[--len] = end;
		end = end->from;
	}
}

/*
** Insere une route dans le tableau de routes a l'aide du pointeur from.
*/

static void	get_route(t_room ***routes, t_room *cur)
{
	int	i;

	i = -1;
	while (1)
		if (cur->flow[++i] == 1)
		{
			cur->link[i]->from = cur;
			if (cur->link[i]->type == 3)
				return (write_route(routes, cur->link[i]));
			cur = cur->link[i];
			i = -1;
		}
}

/*
** Reinitialise les distances dans les salles et marque les salles inutilisees.
*/

static void	clean_bfs(t_room *start)
{
	int	i;
	int	count;

	while (start && !(count = 0))
	{
		if (start->type < 2)
			start->type = 1;
		i = -1;
		while (start->link[++i])
			if (start->flow[i])
				if (start->type < 2)
					start->type = 0;
		start->dist = 0;
		start->from = NULL;
		start = start->next;
	}
}

/*
** Actualise les flux en suivant la route retournee par le bfs.
*/

void		mark_flows(t_room ***route, t_room *start, t_room *end)
{
	int	i;
	int	j;

	i = -1;
	write_route(route, end);
	while ((*route)[++i + 1] && !(j = 0))
	{
		while ((*route)[i]->link[j] != (*route)[i + 1])
			j++;
		(*route)[i]->flow[j] = (*route)[i]->flow[j] == -1 ? 0 : 1;
		j = 0;
		while ((*route)[i + 1]->link[j] != (*route)[i])
			j++;
		(*route)[i + 1]->flow[j] = (*route)[i + 1]->flow[j] == 1 ? 0 : -1;
	}
	clean_bfs(start);
}

/*
** Lis les flux pour en extraire un nouvel univers de routes.
*/

char		read_flows(t_room *start, t_room ****routes)
{
	int	i;
	int	j;

	g_nb.routes++;
	if (!init_routes(routes))
		return (0);
	start->from = NULL;
	i = -1;
	j = -1;
	while (start->link[++i])
		if (start->flow[i] && (start->link[i]->from = start))
			get_route(&(*routes)[++j], start->link[i]);
	return (1);
}
