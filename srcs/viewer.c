/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:40:26 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/27 14:27:59 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/viewer.h"

int				draw_rects(SDL_Renderer *ren, t_room *room, t_coef coef)
{
	SDL_Rect rect;

	while (room)
	{
		SDL_SetRenderDrawColor(ren, 180, 20, 100, SDL_ALPHA_OPAQUE);
		if (room->type == 2)
			if (SDL_SetRenderDrawColor(ren, 15, 230, 51, SDL_ALPHA_OPAQUE))
				return (-1);
		if (room->type == 3)
			if (SDL_SetRenderDrawColor(ren, 100, 25, 230, SDL_ALPHA_OPAQUE))
				return (-1);
		rect = create_rect(room->coord, coef.coefx, coef.coefy);
		if (SDL_RenderDrawRect(ren, &rect))
			return (-1);
		if (SDL_RenderFillRect(ren, &rect))
			return (-1);
		room = room->next;
	}
	return (0);
}

int				draw_lines(SDL_Renderer *ren, t_room *room, t_coef coef)
{
	int i;

	if (SDL_SetRenderDrawColor(ren, 0, 100, 150, SDL_ALPHA_OPAQUE))
		return (-1);
	while (room)
	{
		coef.sx = (int)((float)room->coord[0] * coef.coefx) + 7;
		coef.sy = (int)((float)room->coord[1] * coef.coefy) + 7;
		i = 0;
		while (room->link[i])
		{
			coef.ex = (int)((float)room->link[i]->coord[0] * coef.coefx) + 7;
			coef.ey = (int)((float)room->link[i]->coord[1] * coef.coefy) + 7;
			if (SDL_RenderDrawLine(ren, coef.sx, coef.sy, coef.ex,
				coef.ey) != 0)
				return (-1);
			i++;
		}
		room = room->next;
	}
	return (0);
}

int				draw_routeset(SDL_Renderer *ren, t_room ***routesets,
								t_coef coef)
{
	int i;
	int j;

	i = 0;
	if (SDL_SetRenderDrawColor(ren, 15, 225, 55, SDL_ALPHA_OPAQUE))
		return (-1);
	while (routesets[i] != NULL)
	{
		j = 0;
		while (routesets[i][j + 1] != NULL)
		{
			coef.sx = (int)((float)routesets[i][j]->coord[0] * coef.coefx) + 7;
			coef.sy = (int)((float)routesets[i][j]->coord[1] * coef.coefy) + 7;
			j++;
			coef.ex = (int)((float)routesets[i][j]->coord[0] * coef.coefx) + 7;
			coef.ey = (int)((float)routesets[i][j]->coord[1] * coef.coefy) + 7;
			if (SDL_RenderDrawLine(ren, coef.sx, coef.sy,
			coef.ex, coef.ey) != 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

int				visu(t_room *room, t_room ***routesets)
{
	SDL_Renderer	*ren;
	SDL_Window		*win;
	t_coef			coef;
	SDL_Event		run;

	ren = NULL;
	win = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) \
		|| SDL_CreateWindowAndRenderer(1015, 1015, 0, &win, &ren) \
		|| SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE) \
		|| SDL_RenderClear(ren))
		return (sdl_exit(ren, win));
	coef = get_max(room);
	coef = get_coefs(coef);
	if (draw_rects(ren, room, coef) || draw_lines(ren, room, coef) \
		|| draw_routeset(ren, routesets, coef))
		return (sdl_exit(ren, win));
	SDL_RenderPresent(ren);
	while (1)
		if (SDL_PollEvent(&run))
			if (SDL_QUIT == run.type)
				break ;
	return (sdl_exit(ren, win));
}

int				main(int argc, char **argv)
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
		routesets[1] = NULL;
		visu(room, routesets[0]);
		free_routesets(&routesets);
		free_rooms(&room);
		free(map);
	}
	return (0);
}
