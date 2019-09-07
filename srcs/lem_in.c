/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:09:15 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/23 13:46:30 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Main. Verifie l'input et cherche l'univers le plus adapte au probleme.
*/

int			main(int argc, char **argv)
{
	t_room	****routesets;
	t_room	*room;
	char	*map;

	(void)argv;
	if (argc == 1)
	{
		routesets = NULL;
		room = NULL;
		map = NULL;
		if (!reader(&room, &map) || !(routesets = find_routesets(room)))
			return (error(&map, &room));
		move_ants(routesets[0], &map);
		free_routesets(&routesets);
		free_rooms(&room);
		free(map);
	}
	return (0);
}
