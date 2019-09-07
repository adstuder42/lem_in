/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:21:31 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/27 15:37:47 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Stocke la ligne a afficher dans un buffer.
*/

static void	store_line(char **str, int antnb, char *room)
{
	char	*tmp;

	tmp = NULL;
	ft_join3(str, "L", tmp = ft_itoa(antnb));
	free(tmp);
	ft_join3(str, "-", room);
	ft_join3(str, " ", NULL);
}

/*
** Continue la route pour les fourmis restantes.
*/

static void	follow_route(char **str, t_room ***routes, int *routelen, int *push)
{
	int		nb;
	int		i;
	int		j;
	int		k;

	nb = 1;
	i = 0;
	k = 0;
	while (g_nb.left && ++i < push[0] && (j = -1))
	{
		while (routes[++j] && j < push[i])
			if (push[0] - k <= routelen[j])
			{
				store_line(str, nb + j, routes[j][push[0] - k]->name);
				if (routes[j][push[0] - k]->type == 3)
					g_nb.left--;
			}
		k++;
		nb += j;
	}
}

/*
** Deplace l'ensemble des fourmis dans le graphe en utilisant un seul
** set de routes.
*/

static void	print_steps(t_room ***routes, int *routelen, int *rep, char **map)
{
	int		*push;
	char	*str;
	int		i;
	int		j;

	if (!(push = (int *)malloc(sizeof(int) \
		* (g_nb.ants + routelen[g_nb.routes - 1]))))
		return (ft_putstr_fd("ERROR\n", 2));
	ft_putendl(*map);
	ft_putchar('\n');
	str = NULL;
	push[0] = 1;
	j = g_nb.routes - 1;
	while (g_nb.left)
	{
		follow_route(&str, routes, routelen, push);
		while (j > 0 && push[0] > rep[j] && j--)
			--g_nb.routes;
		i = -1;
		while (++i < g_nb.routes && g_nb.rooms <= g_nb.ants)
			store_line(&str, g_nb.rooms++, routes[i][1]->name);
		push[push[0]++] = i;
		print_cycle(&str);
	}
	free(push);
}

/*
** Calcule la longueur des routes d'un set de routes.
*/

int			*get_routelen(t_room ***routes)
{
	int	*arr;
	int	len;
	int	i;

	len = 0;
	while (routes[len])
		len++;
	if (!(arr = (int *)malloc(sizeof(int) * len)))
		return (NULL);
	i = -1;
	while (routes[++i] && !(len = 0))
	{
		while (routes[i][len])
			len++;
		arr[i] = len - 1;
	}
	return (arr);
}

/*
** Compte le nombre de sets disponible et lance la fonction correspondante.
*/

void		move_ants(t_room ***routes, char **map)
{
	int	*routelen;
	int	*rep;
	int	nbroutes;

	nbroutes = 0;
	while (routes[nbroutes])
		nbroutes++;
	g_nb.routes = nbroutes;
	if (!(routelen = get_routelen(routes)))
		return (ft_putstr_fd("ERROR\n", 2));
	if (!(rep = repartition(routelen, nbroutes, 0)))
		return (ft_putstr_fd("ERROR\n", 2));
	g_nb.rooms = 1;
	g_nb.left = g_nb.ants;
	print_steps(routes, routelen, rep, map);
	free(routelen);
	free(rep);
}
