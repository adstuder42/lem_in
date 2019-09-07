/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:08:20 by thzimmer          #+#    #+#             */
/*   Updated: 2019/05/08 16:28:22 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Copie le tableau de liens et y ajoute la nouvelle addresse.
*/

static char	realloc_links(t_room **from, t_room *to)
{
	t_room	**link;
	int		len;
	int		i;

	len = (*from)->nblinks;
	i = -1;
	while (++i < len)
		if ((*from)->link[i] == to)
			return (1);
	if (!(link = (t_room **)malloc(sizeof(t_room *) * (len + 2))))
		return (0);
	link[len] = to;
	link[len + 1] = NULL;
	i = -1;
	while (++i < len)
		link[i] = (*from)->link[i];
	free((*from)->link);
	(*from)->link = link;
	(*from)->nblinks++;
	return (1);
}

/*
** Recherche la salle de provenance et la salle de destination et envoie leurs
** addresses a realloc_liens.
*/

static char	build_links(t_room **room, char ***names)
{
	t_room	*from;
	t_room	*to;

	from = *room;
	while (from && !ft_strequ(from->name, (*names)[0]))
		from = from->next;
	if (!from)
		return (0);
	to = *room;
	while (to && !ft_strequ(to->name, (*names)[1]))
		to = to->next;
	if (!to)
		return (0);
	if (!realloc_links(&from, to) || !realloc_links(&to, from))
		return (0);
	ft_freetab(names);
	return (1);
}

/*
** Verifie que la salle start n'est pas reliee a end.
*/

char		link_start_end(t_room **start, char **map)
{
	int	nb;
	int	i;

	i = -1;
	while ((*start)->link[++i])
		if ((*start)->link[i]->type == 3 && (nb = 1))
		{
			ft_putendl(*map);
			free(*map);
			ft_putchar('\n');
			while (nb <= g_nb.ants)
				ft_printf("L%d-%s ", nb++, (*start)->next->name);
			ft_putchar('\n');
			free_rooms(start);
			return (1);
		}
	return (0);
}

/*
** Verifie la syntaxe de la ligne representant un lien.
*/

char		check_link_syntax(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	j = i + 1;
	if (line[i])
		while (line[j] && line[j] != '-')
			j++;
	if (!i || line[i] != '-' || line[j])
		return (0);
	return (1);
}

/*
** Itere pour tous les liens.
*/

char		links(char **line, char **map, t_room **room, int tot)
{
	char	**names;

	tot = 0;
	if (!*line)
		return (0);
	while (*line)
	{
		while (*line && (((*line)[0] == '#' && (*line)[1] != '#') \
			|| ((*line)[0] == '#' && (*line)[1] == '#')))
			if (!read_next_line(line, map, "\n", 2))
				return (0);
		if (!*line || !check_link_syntax(*line) \
			|| !(names = ft_strsplit(*line, '-')) || !build_links(room, &names))
		{
			ft_freetab(&names);
			free(*line);
			return (!tot || !(*room)->link ? 0 : 1);
		}
		tot++;
		ft_join3(map, "\n", *line);
		free(*line);
		get_next_line(line);
	}
	return (1);
}
