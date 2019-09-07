/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewertools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 15:29:17 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/27 15:29:18 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/viewer.h"

int				sdl_exit(SDL_Renderer *ren, SDL_Window *win)
{
	if (ren)
		SDL_DestroyRenderer(ren);
	if (win)
		SDL_DestroyWindow(win);
	SDL_Quit();
	return (-1);
}

t_coef			get_max(t_room *room)
{
	t_coef coef;

	coef.xmax = 0;
	coef.ymax = 0;
	while (room)
	{
		if (room->coord[0] > coef.xmax)
			coef.xmax = room->coord[0];
		if (room->coord[1] > coef.ymax)
			coef.ymax = room->coord[1];
		room = room->next;
	}
	return (coef);
}

t_coef			get_coefs(t_coef coef)
{
	coef.coefx = (float)1000 / coef.xmax;
	coef.coefy = (float)1000 / coef.ymax;
	return (coef);
}

SDL_Rect		create_rect(int *coord, float coefx, float coefy)
{
	SDL_Rect rect;

	rect.w = 15;
	rect.h = 15;
	rect.x = (int)((float)coord[0] * coefx);
	rect.y = (int)((float)coord[1] * coefy);
	return (rect);
}
