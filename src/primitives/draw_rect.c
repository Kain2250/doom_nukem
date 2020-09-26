/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:06:54 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/17 21:20:06 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			draw_rect(SDL_Surface *dst, t_rect *rect,
					Uint32 color, int step)
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

static void		while_draw(SDL_Surface *dst, t_rect *rect,
					Uint32 color, int step)
{
	t_rect		cur;

	step = (step == 0) ? 1 : step;
	cur.w = rect->x + rect->w;
	cur.h = rect->y + rect->h;
	cur.y = rect->y;
	while (cur.y < cur.h)
	{
		cur.x = rect->x;
		while (cur.x <= cur.w)
		{
			putpixel(dst, cur.x, cur.y, color);
			cur.x += step;
		}
		cur.y += step;
	}

}

void			draw_feel_rect(SDL_Surface *dst, t_rect *rect,
					Uint32 color, int step)
{
	t_rect		null_rect;

	if (rect == NULL)
		null_rect = rect_fill_no_malloc(0, 0, dst->w, dst->h);
	while_draw(dst, (rect == NULL) ? &null_rect : rect, color, step);
}
