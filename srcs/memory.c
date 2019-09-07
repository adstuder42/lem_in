/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:09:15 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/23 13:46:30 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Libere la memoire et affiche un message sur la sortie d'erreur.
*/

int			error(char **map, t_room **room)
{
	if (*room && link_start_end(room, map))
		return (0);
	free(*map);
	free_rooms(room);
	ft_putstr_fd("ERROR\n", 2);
	return (0);
}

/*
** Libere la memoire des salles.
*/

void		free_rooms(t_room **room)
{
	t_room	*todelete;
	t_room	*next;

	if ((todelete = *room))
	{
		while (todelete)
		{
			next = todelete->next;
			free(todelete->name);
			free(todelete->link);
			free(todelete->flow);
			free(todelete);
			todelete = next;
		}
	}
}

/*
** Libere la memoire des routesets.
*/

void		free_routesets(t_room *****routesets)
{
	int	i;
	int	j;

	if (*routesets && (i = -1))
	{
		while ((*routesets)[++i] && (j = -1))
		{
			while ((*routesets)[i][++j])
				free((*routesets)[i][j]);
			free((*routesets)[i]);
		}
		free(*routesets);
	}
}

/*
** Print un routeset. Un routeset est un 'univers' de routes disponibles en
** meme temps.
*/

void		print_routesets(t_room ****routesets)
{
	int i;
	int	j;
	int	k;

	ft_printf("###### Nombre max de routes : %d ######\n", g_nb.routes);
	ft_printf("\n######### Contenu de routeset ########\n");
	k = -1;
	while (routesets[++k] && (j = -1))
	{
		ft_printf("\n#=#=#=#=#=#=#=# ROUTESET[%d] #=#=#=#=#=#=#=#=#\n", k);
		while (routesets[k][++j] && (i = -1))
		{
			ft_printf("\n-------------- ROUTE[%d] --------------\n", j);
			while (routesets[k][j][++i])
			{
				ft_printf("'routesets[%d][%d]", k, j);
				ft_printf("[%d]->n' = %s\n", i, routesets[k][j][i]->name);
			}
		}
	}
	ft_printf("--------------------------------------\n\n");
}
