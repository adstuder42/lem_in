/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:27:37 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/27 15:34:55 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

/*
** Representation d'une salle.
*/

typedef struct	s_room
{
	struct s_room	**link;
	struct s_room	*next;
	struct s_room	*from;
	int				coord[2];
	char			*flow;
	char			*name;
	int				dist;
	int				nblinks;
	char			type;
}				t_room;

/*
** Structure representant les informations utiles du probleme.
*/

typedef struct	s_glob
{
	int	ants;
	int	rooms;
	int	routes;
	int	left;
}				t_glob;

/*
** Affichage / inutile au projet.
*/

void			print_routesets(t_room ****routesets);

/*
** Fonctions lem-in.
*/

t_room			****find_routesets(t_room *start);
t_room			****find_augmenting_paths(t_room ***first_route, t_room *start);
int				error(char **map, t_room **room);
int				*get_routelen(t_room ***routes);
int				*repartition(int *routelen, int nbroutes, char mod);
int				get_rounds(int *rep, int nbroutes);
char			bfs(t_room ***queue);
char			checker(char **line, char **map, t_room **room, int id);
char			check_link_syntax(char *line);
char			cycle_detection(t_room ***queue);
char			doublon(t_room ****routes);
char			get_coords(t_room **room, char *line);
char			init_routes(t_room ****routes);
char			links(char **line, char **map, t_room **room, int id);
char			link_start_end(t_room **start, char **map);
char			nb_ants(char **line, char **map);
char			realloc_rs(t_room *****routesets, t_room ***routes, int len);
char			reader(t_room **room, char **map);
char			read_flows(t_room *start, t_room ****routes);
char			read_next_line(char **line, char **map, char *str, int id);
char			sort_routesets(t_room *****routesets);
void			free_routesets(t_room *****routesets);
void			free_rooms(t_room **room);
void			mark_flows(t_room ***route, t_room *start, t_room *end);
void			move_ants(t_room ***routes, char **map);
void			print_cycle(char **str);
void			swap_routes(t_room *****routesets, int **routelen, int i[3]);

/*
** Variable globale.
*/

t_glob			g_nb;

#endif
