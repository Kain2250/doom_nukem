/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:06:54 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/04 16:07:20 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			draw_rect(SDL_Surface *dst, t_rect *rect, Uint32 color, int step)
{
	register int	i;
	register int	w;
	register int	h;

	step = (step == 0) ? 1 : step;
	i = rect->x;
	w = rect->x + rect->w;
	h = rect->y + rect->h;
	while (i <= w)
	{
		putpixel(dst, i, rect->y, color);
		putpixel(dst, i, h, color);
		i += step;
	}
	i = rect->y + 1;
	while (i < h)
	{
		putpixel(dst, rect->x, i, color);
		putpixel(dst, w, i, color);
		i += step;
	}
}

void			draw_feel_rect(SDL_Surface *dst, t_rect *rect,
				Uint32 color, int step)
{
	register int	x;
	register int	y;
	register int	w;
	register int	h;

	if (rect == NULL)
		rect = rect_fill(0, 0, dst->w, dst->h);
	step = (step == 0) ? 1 : step;
	w = rect->x + rect->w;
	h = rect->y + rect->h;
	y = rect->y;
	while (y < h)
	{
		x = rect->x;
		while (x <= w)
		{
			putpixel(dst, x, y, color);
			x += step;
		}
		y += step;
	}
	if (rect->free == true)
		free(rect);
}
