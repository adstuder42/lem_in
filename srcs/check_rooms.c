/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:26:56 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/27 15:35:50 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Rempli la structure salle.
*/

static char	create_room(t_room **room, char **name, char type)
{
	t_room	*new;

	if (!*room)
	{
		if (!(*room = (t_room *)malloc(sizeof(t_room))))
			return (0);
		(*room)->name = *name;
		(*room)->type = type;
		if (!((*room)->link = (t_room **)malloc(sizeof(t_room *))))
			return (0);
		(*room)->link[0] = NULL;
		(*room)->next = NULL;
		return (1);
	}
	if (!(new = (t_room *)malloc(sizeof(t_room))))
		return (0);
	new->name = *name;
	new->type = type;
	if (!(new->link = (t_room **)malloc(sizeof(t_room *))))
		return (0);
	new->link[0] = NULL;
	new->next = *room;
	*room = new;
	return (1);
}

/*
** Enregistre la commande pour modifier l'aquisition de la prochaine salle.
*/

static char	get_commands(char **line, char **map, char *type, int id)
{
	*type = 1;
	while (*line && (*line)[0] == '#')
	{
		while ((*line)[0] == '#' && (*line)[1] != '#')
			if (!read_next_line(line, map, "\n", id))
				return (0);
		if (*line && (*line)[0] == '#' && (*line)[1] == '#')
		{
			if (ft_strequ(&(*line)[2], "start"))
				*type = 2;
			else if (ft_strequ(&(*line)[2], "end"))
				*type = 3;
			if (!read_next_line(line, map, "\n", id))
				return (0);
		}
	}
	return (1);
}

/*
** Verifie la syntaxe de la ligne representant une salle et tronque le nom.
*/

static char	check_room_syntax(char **line, char **map, int trunc)
{
	int	i;
	int	j;

	i = 0;
	while ((*line)[i] && (*line)[i] != ' ')
		i++;
	if ((*line)[(trunc = i++)] != ' ')
		return (0);
	j = 0;
	while (ft_isdigit((*line)[i + j]))
		j++;
	if (!ft_check_intmax(&((*line)[i]), j) || !(i += j))
		return (0);
	if ((*line)[i++] != ' ')
		return (0);
	j = 0;
	while (ft_isdigit((*line)[i + j]))
		j++;
	if (!ft_check_intmax(&((*line)[i]), j) || !(i += j))
		return (0);
	if ((*line)[i])
		return (0);
	ft_join3(map, "\n", *line);
	(*line)[trunc] = '\0';
	return (1);
}

/*
** Nombre total de fourmi.
*/

char		nb_ants(char **line, char **map)
{
	int	i;

	i = -1;
	while ((*line)[++i])
		if (!ft_isdigit((*line)[i]))
		{
			free(*line);
			return (0);
		}
	if (!ft_check_intmax(*line, i))
	{
		free(*line);
		return (0);
	}
	if ((g_nb.ants = ft_atoi(*line)))
		*map ? ft_join3(map, "\n", *line) : ft_join3(map, "\0", *line);
	free(*line);
	*line = NULL;
	return (1);
}

/*
** Itere tant que l'input des salles est correct. Passe ensuite aux liens.
*/

char		checker(char **line, char **map, t_room **room, int id)
{
	char	type;

	type = 0;
	while (*line)
	{
		if (!get_commands(line, map, &type, id))
			return (0);
		if (!*line || (*line)[0] == 'L' || ft_strchr(*line, '-') \
			|| !check_room_syntax(line, map, 0))
		{
			free(*line);
			return (id < 3 ? 0 : 1);
		}
		if (!create_room(room, line, type) || !get_coords(room, *line))
			return (0);
		(*room)->nblinks = 0;
		(*room)->flow = NULL;
		id++;
		if (get_next_line(line) < 1 || check_link_syntax(*line))
			break ;
	}
	return (links(line, map, room, (g_nb.rooms = id)));
}
