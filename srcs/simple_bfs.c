/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_bfs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 10:52:51 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/23 13:38:29 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Verifie si la salle est presente dans la queue.
*/

static char	is_tracked(t_room **queue, t_room *room)
{
	int i;

	i = -1;
	while (queue[++i])
		if (room == queue[i])
			return (1);
	return (0);
}

/*
** Recherche la route non decouverte la plus courte sans remonter les flux.
*/

static char	simple_bfs(t_room ***queue)
{
	t_room	*visited;
	int		mark;
	int		i;
	int		j;

	mark = 1;
	i = -1;
	while ((*queue)[++i] && (j = -1))
		while ((visited = (*queue)[i]->link[++j]))
			if (visited->type && !is_tracked(*queue, visited))
			{
				visited->from = (*queue)[i];
				if (visited->type == 3)
					return (1);
				(*queue)[mark] = visited;
				(*queue)[++mark] = NULL;
			}
	return (0);
}

/*
** Detecte d'eventuelles boucles dans les from.
*/

char		cycle_detection(t_room ***queue)
{
	t_room		*cur;
	t_room		*fast;
	t_room		*slow;

	fast = (*queue)[0]->next;
	slow = (*queue)[0]->next;
	while (fast && fast->from)
	{
		slow = slow->from;
		fast = fast->from->from;
		if (fast == slow)
		{
			cur = (*queue)[0];
			while ((cur = cur->next))
				cur->from = NULL;
			(*queue)[1] = NULL;
			return (simple_bfs(queue));
		}
	}
	(*queue)[1] = NULL;
	return (1);
}

/*
** Affiche le cycle et supprime l'espace en fin de ligne.
*/

void		print_cycle(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
		i++;
	(*str)[i - 1] = '\0';
	ft_putendl(*str);
	free(*str);
	*str = NULL;
}
