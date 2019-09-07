/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:27:37 by thzimmer          #+#    #+#             */
/*   Updated: 2019/07/27 15:48:49 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWER_H
# define VIEWER_H

# include "../includes/lem_in.h"
# include <SDL2/SDL.h>

/*
** Structure contenant les informations utiles au viewer.
*/

typedef struct	s_coef
{
	float	coefx;
	float	coefy;
	int		sx;
	int		sy;
	int		ex;
	int		ey;
	int		xmax;
	int		ymax;
}				t_coef;

t_coef			get_max(t_room *room);
t_coef			get_coefs(t_coef coefs);
SDL_Rect		create_rect(int *coord, float coefx, float coefy);
int				draw_rects(SDL_Renderer *ren, t_room *room, t_coef coefs);
int				sdl_exit(SDL_Renderer *ren, SDL_Window *win);

#endif
