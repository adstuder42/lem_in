/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:25:28 by thzimmer          #+#    #+#             */
/*   Updated: 2019/05/08 16:29:02 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Positionne la salle start a la tete de la liste chainee.
*/

static void	get_start(t_room **room)
{
	t_room	*cur;
	t_room	*prev;
	t_room	*tmp;

	cur = *room;
	prev = NULL;
	while (cur)
	{
		if (cur->type == 2)
		{
			if (prev)
				prev->next = *room;
			tmp = cur->next;
			cur->next = (*room)->next;
			(*room)->next = tmp;
			*room = cur;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

/*
** Positionne la salle end en position '->next' de la liste chainee.
*/

static void	get_end(t_room **room)
{
	t_room	*cur;
	t_room	*prev;
	t_room	*tmp;

	cur = *room;
	prev = NULL;
	while (cur)
	{
		if (cur->type == 3)
		{
			if (prev)
				prev->next = (*room)->next;
			tmp = cur->next;
			cur->next = (*room)->next->next;
			(*room)->next->next = tmp;
			(*room)->next = cur;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

/*
** Valide le graphe en comptant les salles start et end.
*/

static char	validate_graph(t_room *room)
{
	int		countstart;
	int		countend;

	countstart = 0;
	countend = 0;
	while (room)
	{
		if (room->type == 2)
			countstart++;
		if (room->type == 3)
			countend++;
		room = room->next;
	}
	if (countstart != 1 || countend != 1)
		return (0);
	return (1);
}

/*
** Stocke la ligne actuelle dans le buffer et acquiere la suivante.
*/

char		read_next_line(char **line, char **map, char *str, int id)
{
	ft_join3(map, str, *line);
	free(*line);
	*line = NULL;
	return (get_next_line(line) <= 0 && id == 1 ? 0 : 1);
}

/*
** Rempli la structure salle avec l'ensemble des pieces, leur affecte un id, un
** nom, un type et les relie. Cree aussi un buffer pour un eventuel affichage.
*/

char		reader(t_room **room, char **map)
{
	char	*line;
	int		i;

	line = NULL;
	if (get_next_line(&line) <= 0)
		return (0);
	if (line[0] == '#')
		if (!read_next_line(&line, map, "\0", 1))
			return (0);
	while (line && line[0] == '#')
		if (!read_next_line(&line, map, "\n", 1))
			return (0);
	if (!nb_ants(&line, map) || get_next_line(&line) < 0 \
		|| !checker(&line, map, room, 1) || !validate_graph(*room))
		return (0);
	get_start(room);
	get_end(room);
	i = -1;
	while ((*room)->link[++i])
		if ((*room)->link[i]->type == 3)
			return (0);
	return (1);
}
